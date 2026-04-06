#include <iostream>
#include <utility>
#include "MyUniquePtr.hpp"
#include "MySharedPtr.hpp"

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

int main() {
    // ───── MyUniquePtr ─────
    std::cout << "=== MyUniquePtr ===\n";

    MyUniquePtr<int> a(new int(42));
    std::cout << "[create] *a=" << *a << "\n";

    std::cout << "[get] ptr=" << a.get() << " val=" << *a.get() << "\n";

    MyUniquePtr<Point> p(new Point(10, 20));
    std::cout << "[->] x=" << p->x << " y=" << p->y << "\n";

    MyUniquePtr<int> b = std::move(a);
    std::cout << "[Move Constructor] *b=" << *b << " a.get()=" << a.get() << "\n";

    MyUniquePtr<int> c(new int(99));
    c = std::move(b);
    std::cout << "[Move Assignment] *c=" << *c << " b.get()=" << b.get() << "\n";

    c.reset(new int(77));
    std::cout << "[reset] *c=" << *c << "\n";

    c.reset();
    std::cout << "[reset(nullptr)] c.get()=" << c.get() << "\n";

    MyUniquePtr<int> d(new int(55));
    int* raw = d.release();
    std::cout << "[release] raw=" << *raw << " d.get()=" << d.get() << "\n";
    delete raw;

    // ───── MySharedPtr ─────
    std::cout << "\n=== MySharedPtr ===\n";

    MySharedPtr<int> sa(new int(100));
    std::cout << "[create] *sa=" << *sa << " use_count=" << sa.use_count() << "\n";

    // 복사 생성자 — ref_count 증가
    MySharedPtr<int> sb = sa;
    std::cout << "[copy] *sb=" << *sb << " use_count=" << sa.use_count() << "\n";

    // 복사 대입 — ref_count 증가
    MySharedPtr<int> sc(new int(999));
    sc = sa;
    std::cout << "[copy assign] *sc=" << *sc << " use_count=" << sa.use_count() << "\n";

    // 이동 생성자 — ref_count 변화 없음
    MySharedPtr<int> sd = std::move(sb);
    std::cout << "[move] *sd=" << *sd << " sb.use_count=" << sb.use_count() << " sa.use_count=" << sa.use_count() << "\n";

    // 이동 대입
    MySharedPtr<int> se(new int(777));
    se = std::move(sc);
    std::cout << "[move assign] *se=" << *se << " use_count=" << sa.use_count() << "\n";

    // operator->
    MySharedPtr<Point> sp(new Point(3, 4));
    std::cout << "[->] x=" << sp->x << " y=" << sp->y << "\n";

    // 스코프 벗어나면 자동 해제 확인
    {
        MySharedPtr<int> tmp(new int(42));
        MySharedPtr<int> tmp2 = tmp;
        std::cout << "[scope] use_count=" << tmp.use_count() << "\n";
    }  // tmp, tmp2 소멸 → ref_count 0 → delete
    std::cout << "[scope end] OK\n";

    return 0;
}