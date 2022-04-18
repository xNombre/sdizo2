#pragma once

#include "Array.hpp"

template<typename T>
class MinHeap {
    Array<T> data;

#ifndef NDEBUG
    void check_max() const;
#endif // NDEBUG

public:
    void push(const T &value);
    const T &top() const;
    void pop();
    const bool empty() const;
};

// For template explicit instantiations
#include "MinHeap.cpp"