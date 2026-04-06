#pragma once
#include <cstddef>

template<typename T>
class MyQueue {
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& val) : data(val), next(nullptr) {}
	};

	Node* _front;
	Node* _back;
	size_t _size;
public:
	MyQueue() {
		this->_front = nullptr;
		this->_back = nullptr;
		this->_size = 0;
	}
	~MyQueue() {
		Node* cur = this->_front;
		while (cur != nullptr) {
			Node* temp = cur->next;
			delete cur;
			cur = temp;
		}
	}

	void push(const T& val) {
		Node* newNode = new Node(val);
		if (this->_size == 0) {
			this->_front = newNode;
			this->_back = newNode;
			_size++;
			return;
		}
		this->_back->next = newNode;
		this->_back = newNode;
		this->_size++;
	}
	void pop() {
		if (this->_size == 0) return;
		Node* removeNode = this->_front;
		this->_front = removeNode->next;
		if (this->_size == 1) this->_back = nullptr;
		delete removeNode;
		this->_size--;
	}
	T& front() {
		return this->_front->data;
	}
	T& back() {
		return this->_back->data;
	}
	bool empty() const {
		return this->_size == 0;
	}
	size_t size() const {
		return this->_size;
	}
};