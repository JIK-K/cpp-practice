#pragma once          // 이 헤더 파일이 여러 번 include 되어도 한 번만 처리되도록 보장
#include <stdexcept>  // std::out_of_range 예외 사용을 위해 포함
#include <cstddef>    // size_t 타입 사용을 위해 포함 (부호 없는 정수, 크기/인덱스 표현)
#include <initializer_list> // std::initializer_list 사용을 위해 포함 (중괄호 초기화 지원)


// ════════════════════════════════════════════════════════════
// ReverseIterator 클래스
// - 역방향 순회를 위한 반복자 클래스
// - 내부 포인터를 감싸서 ++ 연산을 역방향(ptr--)으로 바꿔줌
// - MyVector보다 먼저 선언해야 MyVector 안에서 사용 가능
// ════════════════════════════════════════════════════════════
template <typename T>
class ReverseIterator {
private:
    T* ptr; // 실제 원소를 가리키는 포인터

public:
    // 생성자: 포인터를 받아서 내부 ptr에 저장
    // explicit → ReverseIterator<int> it = somePtr; 같은 암묵적 변환 방지
    explicit ReverseIterator(T* p) : ptr(p) {}

    // * 연산자 오버로딩: 포인터가 가리키는 실제 값을 반환
    // ex) *it → data[i] 값
    T& operator*() { return *ptr; }

    // 전위 ++ 연산자 오버로딩 (++it)
    // 역방향이므로 내부적으로 ptr-- (앞 주소로 이동)
    // *this 반환 → 연산 후 자기 자신을 반환 (체이닝 가능)
    ReverseIterator& operator++() {
        ptr--;
        return *this;
    }

    // 전위 -- 연산자 오버로딩 (--it)
    // 역방향이므로 내부적으로 ptr++ (뒤 주소로 이동)
    ReverseIterator& operator--() {
        ptr++;
        return *this;
    }

    // != 연산자 오버로딩: 두 반복자가 다른 위치를 가리키는지 비교
    // for 루프의 종료 조건에서 사용: it != v.rend()
    bool operator!=(const ReverseIterator& other) const {
        return ptr != other.ptr;
    }

    // == 연산자 오버로딩: 두 반복자가 같은 위치를 가리키는지 비교
    bool operator==(const ReverseIterator& other) const {
        return ptr == other.ptr;
    }
};


// ════════════════════════════════════════════════════════════
// MyVector 클래스
// - 동적 배열(Dynamic Array) 직접 구현
// - std::vector와 동일한 핵심 기능 제공
// - heap 메모리에 연속된 공간을 할당하여 데이터 저장
//
// 핵심 구조:
//   data → [ 1 | 2 | 3 | _ | _ | _ ]
//            ←── sz=3 ───→
//            ←────── cap=6 ──────────→
// ════════════════════════════════════════════════════════════
template <class T>
class MyVector {
private:
    T* data; // heap에 할당된 배열의 시작 주소 (실제 데이터 위치)
    size_t sz;   // 현재 배열에 저장된 원소의 수
    size_t cap;  // heap에 실제로 할당된 공간의 크기 (sz <= cap 항상 유지)

    // ────────────────────────────────────────
    // grow(): 용량이 꽉 찼을 때 메모리를 2배로 늘리는 내부 함수
    // - 외부에서 직접 호출할 필요 없으므로 private에 위치
    // - push_back에서 sz == cap 일 때 자동 호출
    //
    // 동작 순서:
    //   1. 새 용량 계산 (cap이 0이면 1, 아니면 2배)
    //   2. 새 크기의 메모리 할당
    //   3. 기존 데이터를 새 메모리에 복사
    //   4. 기존 메모리 해제
    //   5. 포인터를 새 메모리로 교체
    // ────────────────────────────────────────
    void grow() {
        // cap이 0이면 1로, 아니면 2배로 늘림
        // 2배 성장 전략: 재할당 횟수를 줄여 평균 O(1) 성능 유지
        size_t new_cap = (cap == 0) ? 1 : cap * 2;

        // 새 용량만큼 heap에 메모리 할당
        // new T[n]() → () 덕분에 기본값(0)으로 초기화
        T* new_data = new T[new_cap]();

        // 기존 데이터를 새 메모리로 복사
        for (size_t i = 0; i < sz; i++) {
            new_data[i] = data[i];
        }

        // 기존 메모리 해제 (메모리 누수 방지)
        delete[] data;

        // 포인터와 용량을 새 값으로 교체
        data = new_data;
        cap = new_cap;
    }

public:
    // ────────────────────────────────────────
    // 타입 별칭 (Type Alias)
    // - using 키워드로 타입에 이름을 붙여줌
    // - 외부에서 MyVector<int>::iterator 형태로 사용 가능
    // ────────────────────────────────────────
    using iterator = T*;                // 일반 반복자 (T* 포인터)
    using const_iterator = const T*;          // 읽기 전용 반복자
    using reverse_iterator = ReverseIterator<T>; // 역방향 반복자


    // ════════════════════════════════════════
    // 생성자 / 소멸자
    // ════════════════════════════════════════

    // 기본 생성자: 아무것도 없는 빈 벡터 생성
    // MyVector<int> v;
    // : data(nullptr), sz(0), cap(0) → 멤버 초기화 리스트
    MyVector() : data(nullptr), sz(0), cap(0) {}

    // 크기 지정 생성자: n개의 원소를 0(기본값)으로 초기화
    // MyVector<int> v(5); → {0, 0, 0, 0, 0}
    // explicit → MyVector<int> v = 5; 같은 암묵적 변환 방지
    explicit MyVector(size_t n) : sz(n), cap(n) {
        data = new T[n](); // () → 모든 원소를 0/기본값으로 초기화
    }

    // 초기화 리스트 생성자: 중괄호로 초기값 지정
    // MyVector<int> v = {10, 20, 30};
    // std::initializer_list<T> → 컴파일러가 {10,20,30}을 자동으로 변환해서 넘겨줌
    MyVector(std::initializer_list<T> list) : sz(list.size()), cap(list.size()) {
        data = new T[cap]; // 리스트 크기만큼 메모리 할당
        size_t i = 0;
        // list를 순회하며 data 배열에 복사
        for (const T& val : list) {
            data[i++] = val; // data[0]=10, data[1]=20, data[2]=30 ...
        }
    }

    // 소멸자: 객체가 사라질 때 heap 메모리를 반드시 해제
    // 이걸 안 하면 메모리 누수(memory leak) 발생
    ~MyVector() {
        delete[] data;
    }


    // ════════════════════════════════════════
    // assign: 벡터를 특정 값으로 재초기화
    // v.assign(4, 7) → {7, 7, 7, 7}
    // ════════════════════════════════════════
    void assign(size_t n, const T& val) {
        delete[] data; // 기존 메모리 먼저 해제
        sz = n;
        cap = n;
        data = new T[n]; // 새 메모리 할당
        // n개의 원소를 전부 val로 채움
        for (size_t i = 0; i < n; i++) {
            data[i] = val;
        }
    }


    // ════════════════════════════════════════
    // Iterator: 반복자 반환 함수들
    // - 포인터를 반환하여 배열 순회에 사용
    // ════════════════════════════════════════

    // begin(): 첫 번째 원소의 주소 반환
    // data가 배열의 시작이므로 그대로 반환
    T* begin() { return data; }

    // end(): 마지막 원소의 다음 주소 반환 (경계값, 실제 원소 아님)
    // data + sz → sz번째 인덱스의 주소 (배열 범위 밖)
    T* end() { return data + sz; }

    // const 버전: const 객체에서 호출 시 사용 (읽기 전용)
    const T* begin() const { return data; }
    const T* end()   const { return data + sz; }

    // rbegin(): 역방향 시작 = 마지막 원소의 주소
    // data + sz - 1 → 마지막 원소 위치
    // ReverseIterator로 감싸서 반환 (++이 역방향으로 동작하게)
    reverse_iterator rbegin() { return ReverseIterator<T>(data + sz - 1); }

    // rend(): 역방향 끝 = 첫 번째 원소의 앞 주소 (경계값)
    // data - 1 → 배열 시작보다 한 칸 앞 (순회 종료 감지용)
    reverse_iterator rend() { return ReverseIterator<T>(data - 1); }


    // ════════════════════════════════════════
    // 요소 접근
    // ════════════════════════════════════════

    // at(i): i번째 원소 반환 (범위 검사 있음)
    // i >= sz 이면 std::out_of_range 예외 던짐
    T& at(size_t i) {
        if (i >= sz) throw std::out_of_range("index out of range");
        return data[i];
    }

    // operator[]: i번째 원소 반환 (범위 검사 없음, 빠름)
    // v[i] 문법으로 사용
    // at()과 달리 범위를 벗어나면 undefined behavior
    T& operator[](size_t i) { return data[i]; }

    // front(): 첫 번째 원소 반환 (data[0])
    T& front() { return data[0]; }

    // back(): 마지막 원소 반환 (data[sz-1])
    T& back() { return data[sz - 1]; }


    // ════════════════════════════════════════
    // 삽입 / 삭제
    // ════════════════════════════════════════

    // push_back(): 맨 뒤에 원소 추가
    // sz == cap 이면 grow()로 공간 확보 후 추가
    // data[sz++] = val → 추가 후 sz 1 증가
    void push_back(const T& val) {
        if (sz == cap) grow(); // 공간이 꽉 찼으면 2배로 늘림
        data[sz++] = val;      // 맨 뒤에 삽입 후 크기 증가
    }

    // pop_back(): 맨 뒤 원소 제거
    // 실제로 메모리를 지우지 않고 sz만 줄임 (해당 공간은 덮어쓸 예정)
    void pop_back() {
        if (sz > 0) sz--; // 비어있지 않을 때만 감소
    }

    // insert(pos, val): pos 위치에 val 삽입
    // pos는 포인터(주소값) → begin() + i 형태로 전달
    // ex) v.insert(v.begin() + 1, 99)
    void insert(T* pos, const T& val) {
        // 포인터 - 배열 시작 주소 = 삽입할 인덱스
        size_t idx = pos - data;

        // 공간이 꽉 찼으면 먼저 확장
        // grow() 호출 후 data 주소가 바뀔 수 있으므로 idx로 저장해둔 것
        if (sz == cap) grow();

        // idx 이후 원소들을 한 칸씩 뒤로 밀기 (뒤에서부터 밀어야 덮어쓰지 않음)
        for (size_t i = sz; i > idx; i--) {
            data[i] = data[i - 1];
        }

        // 빈 자리에 새 값 삽입
        data[idx] = val;
        sz++; // 크기 증가
    }

    // clear(): 모든 원소 제거
    // 메모리는 해제하지 않고 sz만 0으로 (capacity는 유지)
    void clear() { sz = 0; }


    // ════════════════════════════════════════
    // 상태 조회
    // ════════════════════════════════════════

    // empty(): 벡터가 비어있으면 true, 원소가 있으면 false
    bool empty() const { return sz == 0; }

    // size(): 현재 저장된 원소의 수 반환
    size_t size() const { return sz; }

    // capacity(): heap에 할당된 실제 공간 크기 반환
    // size() <= capacity() 항상 성립
    size_t capacity() const { return cap; }
};