#include <iostream>
#include "MyQueue.hpp"

int main() {
    MyQueue<int> q;

    // push
    q.push(1);
    q.push(2);
    q.push(3);
    std::cout << "[push 1,2,3] front=" << q.front() << " back=" << q.back() << " size=" << q.size() << "\n";

    // pop — FIFO 확인
    q.pop();
    std::cout << "[pop] front=" << q.front() << " back=" << q.back() << " size=" << q.size() << "\n";

    // pop loop
    while (!q.empty()) {
        std::cout << "[pop loop] front=" << q.front() << "\n";
        q.pop();
    }
    std::cout << "[empty] empty=" << q.empty() << " size=" << q.size() << "\n";

    // 빈 큐 pop — 안터지는지 확인
    q.pop();
    std::cout << "[empty pop] OK\n";

    // 다시 push — 빈 큐에 push 후 정상 동작 확인
    q.push(10);
    q.push(20);
    std::cout << "[re-push] front=" << q.front() << " back=" << q.back() << " size=" << q.size() << "\n";

    return 0;
}