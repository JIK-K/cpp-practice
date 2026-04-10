#pragma once
#include<cstddef>
#include<stdexcept>


template<size_t BLOCK_SIZE, size_t BLOCK_COUNT>
class MemoryPool {
private:
	struct Block {
		Block* next;
	};

	char _pool[BLOCK_SIZE * BLOCK_COUNT]; // 실제 메모리
	Block* _freeList; // 사용가능한 블록 목록

public:
	MemoryPool() {
		for (size_t i = 0; i < BLOCK_COUNT - 1; i++) {
			Block* curr = reinterpret_cast<Block*>(this->_pool + i * BLOCK_SIZE);
			Block* next = reinterpret_cast<Block*>(this->_pool + (i + 1) * BLOCK_SIZE);

			curr->next = next;
		}
		Block* last = reinterpret_cast<Block*>(this->_pool + (BLOCK_COUNT - 1) * BLOCK_SIZE);
		last->next = nullptr;

		this->_freeList = reinterpret_cast<Block*>(this->_pool);
	}
	~MemoryPool() {

	}

	void* allocate() {
		if (this->_freeList == nullptr) throw std::bad_alloc();
		void* res = this->_freeList;
		this->_freeList = this->_freeList->next;
		return res;
	}

	void deallocate(void* ptr) {
		if (!ptr) return;
		Block* block = static_cast<Block*>(ptr);
		block->next = this->_freeList;
		this->_freeList = block;
	}
};