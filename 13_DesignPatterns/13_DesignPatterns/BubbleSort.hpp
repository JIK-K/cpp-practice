#include "ISortStrategy.hpp"

#include <iostream>
#include <algorithm>

class BubbleSort : public ISortStrategy {
public:
	void sort(int* arr, int n) override {
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (arr[j] > arr[j+1]) {
					std::swap(arr[j], arr[j + 1]);
				}
			}
		}
	}
};