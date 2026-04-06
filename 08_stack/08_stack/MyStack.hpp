#pragma once
#include <cstddef>

template <typename T>
class MyStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* _top;
    size_t _size;

public:
    MyStack() {
        this->_top = nullptr;
        _size = 0;
    }
    ~MyStack() {
        Node* cur = this->_top;
        while(cur != nullptr){
            Node* temp = cur->next;
            delete cur;
            cur = temp;
        }
    }

    void push(const T& val) { 
        Node* newNode = new Node(val);
        newNode->next = this->_top;
        this->_top = newNode;
        this->_size++;
    }
    void pop() { 
        if (this->_size == 0) return;
        Node* removeNode = this->_top;
        this->_top = removeNode->next;
        delete removeNode;
        _size--;
    }
    T& top() {
        return this->_top->data;
    }
    bool empty() const {
        return this->_size == 0;
    }
    size_t size()  const {
        return this->_size;
    }
};