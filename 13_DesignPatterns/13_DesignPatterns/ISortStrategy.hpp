#pragma once

class ISortStrategy {
public:
	virtual void sort(int* arr, int n) = 0;
	virtual ~ISortStrategy() = default;
};