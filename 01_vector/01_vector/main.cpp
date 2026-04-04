#include "MyVector.hpp" // 직접 구현한 MyVector 클래스 포함
#include <iostream>     // std::cout 사용을 위해 포함

int main() {

    // ════════════════════════════════════════
    // 벡터 생성
    // ════════════════════════════════════════

    MyVector<int> v1;                       // 빈 벡터 (size=0, capacity=0)
    MyVector<int> v2(5);                    // 원소 5개, 전부 0으로 초기화 → {0,0,0,0,0}
    MyVector<int> v3 = { 10, 20, 30, 40 }; // 초기화 리스트로 생성 → {10,20,30,40}


    // ════════════════════════════════════════
    // assign: 벡터를 특정 값으로 재초기화
    // assign(개수, 값)
    // ════════════════════════════════════════

    MyVector<int> v4;
    v4.assign(4, 7); // v4 → {7, 7, 7, 7}

    std::cout << "v4 (assign 4, 7): ";
    for (auto& x : v4) std::cout << x << " "; // 7 7 7 7
    std::cout << "\n";


    // ════════════════════════════════════════
    // push_back / pop_back
    // push_back: 맨 뒤에 원소 추가
    // pop_back:  맨 뒤 원소 제거
    // ════════════════════════════════════════

    v1.push_back(1); // v1 → {1}
    v1.push_back(2); // v1 → {1, 2}
    v1.push_back(3); // v1 → {1, 2, 3}
    v1.pop_back();   // v1 → {1, 2}

    std::cout << "v1 (push 1,2,3 후 pop): ";
    for (auto& x : v1) std::cout << x << " "; // 1 2
    std::cout << "\n";


    // ════════════════════════════════════════
    // insert: 원하는 위치에 원소 삽입
    // insert(위치의 주소값, 삽입할 값)
    // begin() + 1 → 1번 인덱스 위치
    // ════════════════════════════════════════

    v3.insert(v3.begin() + 1, 99); // v3 → {10, 99, 20, 30, 40}

    std::cout << "v3 (insert 99 at [1]): ";
    for (auto& x : v3) std::cout << x << " "; // 10 99 20 30 40
    std::cout << "\n";


    // ════════════════════════════════════════
    // 요소 접근
    // at(i)    → i번째 원소, 범위 검사 있음 (예외 발생 가능)
    // v[i]     → i번째 원소, 범위 검사 없음 (빠름)
    // front()  → 첫 번째 원소
    // back()   → 마지막 원소
    // ════════════════════════════════════════

    std::cout << "at(1)     : " << v3.at(1) << "\n"; // 99
    std::cout << "v3[0]     : " << v3[0] << "\n"; // 10
    std::cout << "front()   : " << v3.front() << "\n"; // 10
    std::cout << "back()    : " << v3.back() << "\n"; // 40


    // ════════════════════════════════════════
    // 상태 조회
    // size()     → 실제 원소 수
    // capacity() → 할당된 공간 크기
    // empty()    → 비어있으면 true
    // ════════════════════════════════════════

    std::cout << "size      : " << v3.size() << "\n"; // 5
    std::cout << "capacity  : " << v3.capacity() << "\n"; // 8 (grow로 2배씩 증가)
    std::cout << "empty     : " << v3.empty() << "\n"; // 0 (false)


    // ════════════════════════════════════════
    // begin / end: 정방향 순회
    // range-based for 루프 내부적으로 begin()/end() 사용
    // ════════════════════════════════════════

    std::cout << "v3 정방향: ";
    for (auto& x : v3) std::cout << x << " "; // 10 99 20 30 40
    std::cout << "\n";


    // ════════════════════════════════════════
    // rbegin / rend: 역방향 순회
    // rbegin() → 마지막 원소부터 시작
    // rend()   → 첫 번째 원소 앞에서 종료
    // ++it     → 내부적으로 ptr-- (역방향 이동)
    //
    // 순회 방향:
    //   {10, 99, 20, 30, 40}
    //              ↑ rbegin (40)
    //    ↑ rend 경계 (10 앞)
    // ════════════════════════════════════════

    std::cout << "v3 역방향: ";
    // MyVector<int>::reverse_iterator → ReverseIterator<int> 타입
    MyVector<int>::reverse_iterator it = v3.rbegin();
    for (it = v3.rbegin(); it != v3.rend(); ++it) { // ++it → 내부적으로 ptr--
        std::cout << *it << " "; // 40 30 20 99 10
    }
    std::cout << "\n";


    // ════════════════════════════════════════
    // clear: 모든 원소 제거 (sz=0, capacity는 유지)
    // ════════════════════════════════════════

    v3.clear();
    std::cout << "clear 후 size    : " << v3.size() << "\n"; // 0
    std::cout << "clear 후 capacity: " << v3.capacity() << "\n"; // 그대로 유지
    std::cout << "clear 후 empty   : " << v3.empty() << "\n"; // 1 (true)

    return 0;
}