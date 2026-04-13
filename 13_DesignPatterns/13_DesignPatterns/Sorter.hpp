#pragma once

#include "ISortStrategy.hpp"

class Sorter {
private:
	ISortStrategy* _strategy;
public:
	~Sorter() { delete _strategy; }
	void setStrategy(ISortStrategy* s) {
		this->_strategy = s;
	}

	void sort(int* arr, int n) {
		this->_strategy->sort(arr, n);
	}
};