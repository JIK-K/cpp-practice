//#include<iostream>
//#include<thread>
//#include<mutex>
//#include<condition_variable>
//#include<queue>
//#include<vector>
//
//template<typename T>
//class ThreadSafeQueue {
//private:
//	std::queue<T> _queue;
//	std::mutex _mtx;
//	std::condition_variable _cv;
//	bool _done = false;
//
//public:
//	void push(const T& val) {
//		// lock 걸고 push, cv notify
//		std::unique_lock<std::mutex> lock(_mtx);
//		this->_queue.push(val);
//		std::cout << "[push] : " << val << std::endl;
//		this->_cv.notify_one();
//	}
//
//	bool pop(T& val) {
//		// 데이터 올때까지 대기 pop
//		std::unique_lock<std::mutex> lock(_mtx);
//		this->_cv.wait(lock, [this] {
//			return !this->_queue.empty() || this->_done;
//			});
//		if (this->_queue.empty() && this->_done) return false;
//
//		val = std::move(this->_queue.front());
//		this->_queue.pop();
//		return true;
//	}
//
//	void done() {
//		// 끝났다고알림
//		std::unique_lock<std::mutex> lock(_mtx);
//		this->_done = true;
//		this->_cv.notify_all();
//	}
//};
//
//int main() {
//	ThreadSafeQueue<int> q;
//
//	std::thread p1([&q]() {
//		for (int i = 0; i < 10; i++) {
//			q.push(i + 1);
//		}
//		});
//	std::thread p2([&q]() {
//		for (int i = 10; i < 20; i++) {
//			q.push(i + 1);
//		}
//		});
//
//	std::thread c1([&q]() {int val; while (q.pop(val)) {
//		std::cout << "[c1] : " << val << std::endl;
//	}});
//
//	std::thread c2([&q]() {int val; while (q.pop(val)) {
//		std::cout << "[c2] : " << val << std::endl;
//	}});
//
//	p1.join();
//	p2.join();
//	q.done();
//
//	c1.join();
//	c2.join();
//
//	return 0;
//}

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<vector>
#include<functional>
#include<atomic>
#include<random>

enum class Priority {
	HIGH = 0,
	MEDIUM = 1,
	LOW = 2
};

static std::mutex count_mtx;


struct Task {
	int id;
	Priority priority;
	std::function<void(int, Priority)> job;

	bool operator<(const Task& o) const {
		return priority > o.priority;
	}
};

class PriorityScheduler {
private:
	std::priority_queue<Task> _queue;
	std::mutex _mtx;
	std::condition_variable _cv;
	std::atomic<bool> _done{ false };
	std::vector<std::thread> _workers;
	std::atomic<int> _completed{ 0 };
	int _total = 0;

	void workerLoop() {
		while (true) {
			Task task;
			{
				std::unique_lock<std::mutex> lock(_mtx);
				_cv.wait(lock, [this] {
					return !this->_queue.empty() || this->_done;
					});

				if (this->_queue.empty() && this->_done) return;

				task = _queue.top();
				_queue.pop(); 
			}
			task.job(task.id, task.priority);
			_completed++;
			this->_cv.notify_all();
		}
	}
public:
	PriorityScheduler(int numWorkers) {
		for (int i = 0; i < numWorkers; i++) {
			_workers.emplace_back([this]() {
				workerLoop();
			});
		}
	}
	~PriorityScheduler() {
		this->shutdown();
		for (std::thread& t : _workers) {
			if (t.joinable()) t.join();
		}
	}

	void submit(int id, Priority priority, std::function<void(int, Priority)> job) {
		// Task 추가
		std::unique_lock<std::mutex> lock(_mtx);
		this->_queue.push({ id, priority, job });
		_total++;
		_cv.notify_one();
	}
		
	void shutdown() {
		this->_done = true;
		this->_cv.notify_all();
	}

	void waiting() {
		std::unique_lock<std::mutex> lock(_mtx);
		_cv.wait(lock, [this]() {
			return _completed == _total;
		});
	}
};

void printTask(int a, Priority priority) {
	std::lock_guard<std::mutex> lock(count_mtx);
	std::cout << "[Thread " << std::this_thread::get_id() << "] Task - " << a << "Priority - " << static_cast<int>(priority) << std::endl;

}

int main() {
	PriorityScheduler ps(3);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);
	for(int i = 0; i < 10; i++){
		Priority priority = static_cast<Priority>(dis(gen));

		ps.submit(i, priority, printTask);
	}

	ps.waiting();
	ps.shutdown();

	return 0;
}