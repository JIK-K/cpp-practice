#pragma once

template <typename T>
class MySharedPtr {
private:
	T* _ptr;
	int* _ref_count;
public:
	// 생성자
	explicit MySharedPtr(T* p = nullptr) {
		this->_ptr = p;
		this->_ref_count = (p != nullptr) ? new int(1) : nullptr;
	}
	// 소멸자
	~MySharedPtr() {
		if (this->_ref_count == nullptr) return;
		(*this->_ref_count)--;

		if (*this->_ref_count == 0) {
			delete this->_ptr;
			delete this->_ref_count;
		}
	}

	// 복사 생성자 / 복사 대입 연산자
	MySharedPtr(const MySharedPtr& o) {
		this->_ptr = o._ptr;
		this->_ref_count = o._ref_count;
		(*this->_ref_count)++;
	}
	MySharedPtr& operator=(const MySharedPtr& o) {
		if (this == &o) return *this;
		(*this->_ref_count)--;

		if (*this->_ref_count == 0) {
			delete this->_ptr;
			delete this->_ref_count;
		}

		this->_ptr = o._ptr;
		this->_ref_count = o._ref_count;
		(*this->_ref_count)++;
		return *this;
	}

	// 이동 생성자 / 이동 대입 생성자
	MySharedPtr(MySharedPtr&& o) {
		this->_ptr = o._ptr;
		this->_ref_count = o._ref_count;

		o._ptr = nullptr;
		o._ref_count = nullptr;
	}
	MySharedPtr& operator=(MySharedPtr&& o) {
		if (this == &o) return *this;
		
		(*this->_ref_count)--;
		if (*this->_ref_count == 0) {
			delete this->_ptr;
			delete this->_ref_count;
		}

		this->_ptr = o._ptr;
		this->_ref_count = o._ref_count;

		o._ptr = nullptr;
		o._ref_count = nullptr;

		return *this;
	}

	// 연산자
	T& operator*() {
		return *this->_ptr;
	}
	T* operator->() {
		return this->_ptr;
	}

	// etc
	T* get() const {
		return this->_ptr;
	}
	int use_count() const {
		return this->_ref_count ? *this->_ref_count : 0;
	}
};