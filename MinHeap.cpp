#pragma once

#include <iostream>

#include "MinHeap.hpp"

#define PARENT_OF(child) (((child)-1) / 2)
#define L_CHILD_OF(parent) (((parent)*2 + 1))
#define R_CHILD_OF(parent) (((parent)*2 + 2))

template <typename T>
void MinHeap<T>::push(const T &value)
{
    size_t pos = data.size();

    data.resize(pos + 1);
    data[pos] = value;

    // Heapify upwards
    while (pos != 0) {
        if (data[pos] < data[PARENT_OF(pos)])
            std::swap(data[pos], data[PARENT_OF(pos)]);
        pos = PARENT_OF(pos);
    }
}

template <typename T>
const T &MinHeap<T>::top() const
{
    if (data.size() == 0)
        throw std::runtime_error("MinHeap is empty");

    return data[0];
}

template <typename T>
void MinHeap<T>::pop()
{
    size_t max = data.size();

    // Always remove from top - index = 0
    size_t index = 0;

    if (max == 0)
        throw std::runtime_error("MinHeap is empty");

    // moved from variable definition
    max--;

    data[index] = data[max];
    data.resize(max);

    // Heapify downwards
    while (1) {
        size_t child = L_CHILD_OF(index);
        size_t candidate = index;

        if (child < max && data[candidate] > data[child])
            candidate = child;

        child = R_CHILD_OF(index);
        if (child < max && data[candidate] > data[child])
            candidate = child;

        if (candidate != index) {
            std::swap(data[index], data[candidate]);
            index = candidate;
        }
        else
            break;
    }
}

template <typename T>
const bool MinHeap<T>::empty() const
{
    return data.empty();
}