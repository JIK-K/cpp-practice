#include<iostream>
#include <string>
#include<chrono>
#include"MemoryPool.hpp"

#define BLOCK_SIZE 8
#define BLOCK_COUNT 10

int main() {
	MemoryPool<BLOCK_SIZE, BLOCK_COUNT> p;

	// 1. 기본 할당 / 해제
	std::cout << "[Test 1] : Allco / Dealloc" << std::endl;
	int* a = static_cast<int*>(p.allocate());
	*a = 410;
	std::cout << *a << std::endl;
	p.deallocate(a);

	// 2. 여러 개 할당 후 해제
	std::cout << "[Test 2] : Multi Alloc" << std::endl;
	char* multi[BLOCK_COUNT];
	for (int i = 0; i < BLOCK_COUNT; i++) {
		multi[i] = static_cast<char*>(p.allocate());
		std::cout << "Alloc[ " << i << " ]" << (void*)multi[i] << std::endl;
	}

	// 3. 풀 가득 찼을때 bad_alloc 발생
	std::cout << "[Test 3] : Pool Exhaustion" << std::endl;
	try {
		p.allocate();
	}
	catch (const std::bad_alloc& e) {
		std::cout << "Caught expected exception : " << e.what() << std::endl;
	}

	// 4. 해제 후 재할당
	std::cout << "[Test 4] : Reuse Blocks" << std::endl;
	char* temp = multi[3];
	p.deallocate(temp);
	char* newBlock = static_cast<char*>(p.allocate());
	std::cout << "Previous [3] Block : " << (void*)temp << std::endl;
	std::cout << "New Allocated Block : " << (void*)newBlock << std::endl;
	if (temp == newBlock) std::cout << "Result: Address Reused Success!" << std::endl;

	// 모든 메모리 반납
	for (int i = 0; i < BLOCK_COUNT - 1; i++) p.deallocate(multi[i]);

	// 5. new / delete vs memory pool 성능 비교
	std::cout << "[Test 5] : Performance Comparison" << std::endl;
	const int ITERATIONS = 1000000;

	// MemoryPool 성능 측정
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < ITERATIONS; ++i) {
		void* ptr = p.allocate();
		p.deallocate(ptr);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> poolDiff = end - start;
	std::cout << "MemoryPool Time : " << poolDiff.count() << "s" << std::endl;
	
	// new/delete 성능 측정
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < ITERATIONS; ++i) {
		char* p = new char[BLOCK_SIZE];
		delete[] p;
	}
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> stdDiff = end - start;
	std::cout << "new/delete Time : " << stdDiff.count() << "s" << std::endl;

	// new / delete → OS에 메모리 요청 → heap 탐색 → 단편화 관리
	// MemoryPool → 이미 할당된 공간에서 포인터만 교체 → O(1)
	std::cout << "Speedup: " << stdDiff.count() / poolDiff.count() << "x" << std::endl;
}