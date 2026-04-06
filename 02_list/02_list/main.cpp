#include <iostream>
#include "MyList.hpp"

void print(MyList<int>& lst, const std::string& label) {
    std::cout << "[" << label << "] ";
    for (auto it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << " ";
    std::cout << "(size=" << lst.size() << ")\n";
}

int main() {
    MyList<int> lst;

    // push_back / push_front
    lst.push_back(2);
    lst.push_back(3);
    lst.push_front(1);
    print(lst, "push_back(2,3), push_front(1)");

    // front / back
    std::cout << "[front/back] " << lst.front() << " / " << lst.back() << "\n";

    // insert — begin()의 다음(2) 앞에 99 삽입
    auto it = lst.begin();
    ++it;
    lst.insert(it, 99);
    print(lst, "insert(99) before 2");

    // erase — 99 제거
    it = lst.begin();
    ++it;
    lst.erase(it);
    print(lst, "erase(99)");

    // pop_back / pop_front
    lst.pop_back();
    lst.pop_front();
    print(lst, "pop_back, pop_front");

    // clear
    lst.push_back(10);
    lst.push_back(20);
    lst.clear();
    std::cout << "[clear] empty=" << lst.empty() << " size=" << lst.size() << "\n";

    // 빈 리스트 pop — 안터지는지 확인
    lst.pop_back();
    lst.pop_front();
    std::cout << "[empty pop] OK\n";

    return 0;
}