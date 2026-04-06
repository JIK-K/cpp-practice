#pragma once

template <typename T>
class MyUniquePtr {
private:
	T* _ptr;
public:
	// 생성자
	explicit MyUniquePtr(T* p = nullptr) {
		this->_ptr = p;
	}
	// 소멸자
	~MyUniquePtr() {
		delete this->_ptr;
	}

	// 복사 금지
	MyUniquePtr(const MyUniquePtr&) = delete;
	MyUniquePtr& operator=(const MyUniquePtr&) = delete;

	// 이동 생성자 / 이동 대입 생성자
	MyUniquePtr(MyUniquePtr&& o) {
		this->_ptr = o._ptr;
		o._ptr = nullptr;
	}
	MyUniquePtr& operator=(MyUniquePtr&& o) {
		if (this == &o) return *this; // 자기 자신 대입 방지
		delete this->_ptr;
		this->_ptr = o._ptr;
		o._ptr = nullptr;
		return *this;
	}

	// 연산자 오버로딩
	T& operator*() {
		return *this->_ptr;
	}
	T* operator->() {
		return this->_ptr;
	}

	// etc
	T* get() const {
		//내부 포인터 반환
		return this->_ptr;
	}
	void reset(T* p = nullptr) {
		// 기존 해제 후 교체
		if (this->_ptr == p) return;
		delete this->_ptr;
		this->_ptr = p;
	}
	T* release() {
		// 소유권 포기, 포인터 반환
		T* tempPtr = this->_ptr;
		this->_ptr = nullptr;
		return tempPtr;
	}
};