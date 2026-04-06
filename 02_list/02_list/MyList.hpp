#pragma once
#include <cstddef>
#include <stdexcept>

template <typename T>
class MyList {
private:
	struct Node {
		T data;
		Node* prev;
		Node* next;
		Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
	};
	Node* head;
	Node* tail;
	size_t _size;
public:
	struct Iterator {
		Node* ptr;
		Iterator(Node* p) : ptr(p) {}

		T& operator*() {
			return this->ptr->data;

		}
		Iterator& operator++() {
			this->ptr = this->ptr->next;
			return *this;
		}
		Iterator& operator--() {
			this->ptr = this->ptr->prev;
			return *this;
		}
		bool operator==(const Iterator& o) const {
			return this->ptr == o.ptr;
		}
		bool operator!=(const Iterator& o) const {
			return !(*this == o);
		}
	};
	MyList() {
		// sentinel 노드 2개 만들고 head <-> tail 연결
		this->head = new Node(T{});
		this->tail = new Node(T{});
		this->head->next = this->tail;
		this->tail->prev = this->head;
		this->_size = 0;
	}
	~MyList() {
		// clear() 호출 후 sentinel 노드 해제
		this->clear();
		delete this->head;
		delete this->tail;
	}

	// ───── Element Access ─────
	T& front() {
		return this->head->next->data;
	}
	T& back() { 
		return this->tail->prev->data;
	}

	// ───── Iterators ─────
	Iterator begin() { 
		// head->next 반환
		return this->head->next;
	}
	Iterator end() { 
		//tail 반환 
		return this->tail;
	}

	// ───── Capacity ─────
	bool empty() const {
		return _size == 0;
	}
	size_t size()  const {
		return _size;
	}

	// ───── Modifiers ─────
	void push_back(const T& val) {
		// tail 앞에 삽입
		Node* newNode = new Node(val);
		newNode->next = this->tail;
		newNode->prev = this->tail->prev;
		this->tail->prev->next = newNode;
		this->tail->prev = newNode;
		_size++;
	}
	void push_front(const T& val) {
		// head 뒤에 삽입
		Node* newNode = new Node(val);
		newNode->next = this->head->next;
		newNode->prev = this->head;
		this->head->next->prev = newNode;
		this->head->next = newNode;
		_size++;
	}
	void pop_back() { 
		// tail 앞 노드 제거
		if (_size == 0) return;
		Node* removeNode = this->tail->prev;
		this->tail->prev = removeNode->prev;
		removeNode->prev->next = this->tail;

		delete removeNode;
		_size--;
	}
	void pop_front() { 
		//TODO: head 뒤 노드 제거
		if (_size == 0) return;
		Node* removeNode = this->head->next;
		this->head->next = removeNode->next;
		removeNode->next->prev = this->head;

		delete removeNode;
		_size--;
	}

	Iterator insert(Iterator it, const T& val) {
		// it 앞에 val 삽입, 삽입된 노드의 iterator 반환
		Node* newNode = new Node(val);
		newNode->next = it.ptr;
		newNode->prev = it.ptr->prev;
		it.ptr->prev->next = newNode;
		it.ptr->prev = newNode;

		_size++;
		return Iterator(newNode);
	}

	Iterator erase(Iterator it) {
		// it가 가리키는 노드 제거, 다음 노드의 iterator 반환
		Node* removeNode = it.ptr;
		Node* nextNode = removeNode->next;
		removeNode->prev->next = removeNode->next;
		removeNode->next->prev = removeNode->prev;

		_size--;
		delete removeNode;
		return Iterator(nextNode);
	}

	void clear() {
		// 모든 노드 삭제, sentinel은 유지
		Node* cur = this->head->next;
		while (cur != this->tail) {
			Node* temp = cur->next;
			delete cur;
			cur = temp;
		}
		this->head->next = this->tail;
		this->tail->prev = this->head;
		this->_size = 0;
	}

private:
	// 내부 헬퍼: pos 앞에 노드 삽입
	Iterator _insert_before(Node* pos, const T& val) { /* TODO */ }

	// 내부 헬퍼: 특정 노드 제거
	Iterator _erase(Node* pos) { /* TODO */ }
};