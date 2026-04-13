#include<iostream>
#include<vector>
#include<random>

#include "Sorter.hpp"
#include "BubbleSort.hpp"
#include "QuickSort.hpp"


void printArr(const std::vector<int>& arr) {
	for (const auto& v : arr)
		std::cout << "[" << v << "]";
	std::cout << "\n";
}

void testStrategy() {
	std::vector<int> arr;
	std::vector<int>::iterator it;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 99);

	for (int i = 0; i < 10; i++) {
		arr.push_back(dis(gen));
	}

	Sorter st;
	// BubbleSort
	std::cout << "[Before BubbleSort] ";
	printArr(arr);

	st.setStrategy(new BubbleSort());
	st.sort(arr.data(), arr.size());
	
	std::cout << "[After BubbleSort]  ";
	printArr(arr);

	std::shuffle(arr.begin(), arr.end(), gen);

	// QuickSort
	std::cout << "[Before QuickSort]  ";
	printArr(arr);

	st.setStrategy(new QuickSort());
	st.sort(arr.data(), arr.size());
	
	std::cout << "[After QuickSort]   ";
	printArr(arr);
}