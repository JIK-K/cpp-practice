#include<iostream>
#include<chrono>

int main() {
	const int ITERATIONS = 1000000;

	// ───── Stack 성능 측정 ─────
	// 스택 변수 선언 후 값 쓰기 반복
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < ITERATIONS; i++) {
		int a = i;
		(void)a;
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> stackTime = end - start;
	std::cout << "Stack Time : " << stackTime.count() << "\n";

	// ───── Heap 성능 측정 ─────
	// new/delete 반복
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < ITERATIONS; i++) {
		int* a = new int(i);
		delete a;
	}
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> heapTime = end - start;
	std::cout << "Heap Time : " << heapTime.count() << "\n";

	// ───── 결과 출력 ─────
	// 시간 비교 + 몇 배 차이인지
	std::cout << "Speedup    : " << heapTime.count() / stackTime.count() << "x\n";
	/*
	* 
	* 
		1. 스택이 힙보다 120배 빠름
		Stack : 0.0017s
		Heap  : 0.2085s

		2. 왜 이렇게 차이나냐면:
		Stack → 스택 포인터만 이동 (push/pop)
				컴파일 타임에 크기 확정
				OS 개입 없음

		Heap  → OS에 메모리 요청
				빈 공간 탐색 (free list 순회)
				단편화 관리
				→ 이 모든 과정이 매번 발생

		3. 근데 스택을 항상 쓸 수 없는 이유:
		크기가 컴파일 타임에 확정돼야 함
		크기가 제한적 (보통 1~8MB)
		함수 끝나면 사라짐

		4. 그래서 memory pool이 존재하는 이유:
		힙에 미리 크게 잡아두고
		pool 내부에서 스택처럼 포인터만 이동
		→ 힙의 유연함 + 스택의 속도
		→ 아까 memory pool이 21배 빠른 이유
	*/
}