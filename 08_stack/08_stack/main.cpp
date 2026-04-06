#include <iostream>
#include "MyStack.hpp"

int main() {
    MyStack<int> st;

    // push
    st.push(1);
    st.push(2);
    st.push(3);
    std::cout << "[push 1,2,3] top=" << st.top() << " size=" << st.size() << "\n";

    // pop
    st.pop();
    std::cout << "[pop] top=" << st.top() << " size=" << st.size() << "\n";

    // empty 체크 후 top 접근 (임베디드 컨벤션)
    while (!st.empty()) {
        std::cout << "[pop loop] top=" << st.top() << "\n";
        st.pop();
    }
    std::cout << "[empty] empty=" << st.empty() << " size=" << st.size() << "\n";

    // 빈 스택 pop — 안터지는지 확인
    st.pop();
    std::cout << "[empty pop] OK\n";

    return 0;
}