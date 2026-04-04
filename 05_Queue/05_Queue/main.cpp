#include<iostream>
#include<windows.h>

using namespace std;

template <class T>
class myQueue {
private:
	T* arr;
	int q_size;
	int front;
	int rear;
public:
	myQueue() : arr(nullptr), q_size(0), front(0), rear(0) {}
	~myQueue() {
		delete[] arr;
	}

	void InitQueue(int size) {
		delete[] arr;
		q_size = size;
		arr = new T[size];
		front = 0;
		rear = 0;
	}

	bool empty() {
		return rear == front;
	}
	int size() {
		return rear - front;
	}
	bool push(T data) {
		if (rear == q_size) return false; 
		arr[rear] = data;
		rear++;
		return true;
	}
	T pop() {
		T data = arr[front];
		front++;
		return data;
	}
};

static myQueue<int> q;

bool Insert(int data) {
	return q.push(data);
}

void  PrintQueue() {
	if (q.empty()) {
		cout << "대기 중인 문서가 없습니다" << endl;
	}
	int waitingDocument = q.size();

	cout << "대기중인 문서 수 : " << waitingDocument << endl;
}

int Delete() {
	if (q.empty()) return -1;
	int page = q.pop();
	return page;
}


int main() {
	int total = 5;
	int processed = 0;
	int time = 0;
	int nextTime = 0;
	int currentPage = 0;

	q.InitQueue(100);

	cout << "인쇄 대기중..." << endl;

	while (processed < total || !q.empty() || currentPage > 0) {
		if (time == nextTime && processed < total) {
			int pages = rand() % 9 + 2;
			Insert(pages);
			cout << pages << "페이지짜리 새 문서 삽입" << endl;
			PrintQueue();
			nextTime += 5;
			processed++;
		}

		if (currentPage == 0 && !q.empty()) {
			currentPage = Delete();
		}

		if (currentPage > 0) {
			cout << currentPage << "페이지 인쇄 중..." << endl;
			currentPage--;
		}
		
		time++;
		Sleep(1);
	}
	
}