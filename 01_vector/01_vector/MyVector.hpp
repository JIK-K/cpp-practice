#pragma once
#include <stdexcept>
#include <cstddef>
#include <initializer_list>

template <typename T>
class ReverseIterator {
private:
    T* ptr;
public:
    explicit ReverseIterator(T* p) : ptr(p) {}

    T& operator*() { return *ptr; }
    ReverseIterator& operator++() { ptr--; return *this; }
    ReverseIterator& operator--() { ptr++; return *this; }
    bool operator!=(const ReverseIterator& o) const { return ptr != o.ptr; }
    bool operator==(const ReverseIterator& o) const { return ptr == o.ptr; }
};

template <typename T>
class MyVector {
private:
    T* data;
    size_t sz;
    size_t cap;

    void grow() {
        size_t new_cap = (cap == 0) ? 1 : cap * 2;
        T* new_data = new T[new_cap]();
        for (size_t i = 0; i < sz; i++)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
        cap = new_cap;
    }

public:
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = ReverseIterator<T>;

    // ───── Constructor / Destructor ─────
    MyVector() : data(nullptr), sz(0), cap(0) {}

    explicit MyVector(size_t n) : sz(n), cap(n) {
        data = new T[n]();
    }

    MyVector(std::initializer_list<T> list) : sz(list.size()), cap(list.size()) {
        data = new T[cap];
        size_t i = 0;
        for (const T& val : list)
            data[i++] = val;
    }

    ~MyVector() { delete[] data; }

    // ───── Assign ─────
    void assign(size_t n, const T& val) {
        delete[] data;
        sz = cap = n;
        data = new T[n];
        for (size_t i = 0; i < n; i++)
            data[i] = val;
    }

    // ───── Iterators ─────
    T* begin() { return data; }
    T* end() { return data + sz; }
    const T* begin() const { return data; }
    const T* end()   const { return data + sz; }

    reverse_iterator rbegin() { return ReverseIterator<T>(data + sz - 1); }
    reverse_iterator rend() { return ReverseIterator<T>(data - 1); }

    // ───── Element Access ─────
    T& at(size_t i) {
        if (i >= sz) throw std::out_of_range("index out of range");
        return data[i];
    }
    T& operator[](size_t i) { return data[i]; }
    T& front() { return data[0]; }
    T& back() { return data[sz - 1]; }

    // ───── Modifiers ─────
    void push_back(const T& val) {
        if (sz == cap) grow();
        data[sz++] = val;
    }

    void pop_back() {
        if (sz > 0) sz--;
    }

    void insert(T* pos, const T& val) {
        size_t idx = pos - data;
        if (sz == cap) grow();
        for (size_t i = sz; i > idx; i--)
            data[i] = data[i - 1];
        data[idx] = val;
        sz++;
    }

    void clear() { sz = 0; }

    // ───── Capacity ─────
    bool   empty()    const { return sz == 0; }
    size_t size()     const { return sz; }
    size_t capacity() const { return cap; }
};