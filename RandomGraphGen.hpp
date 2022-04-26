#pragma once

#include <random>

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"

static std::random_device rd;
static std::default_random_engine generator(rd());

class RandomGraphGen {

    template <typename T>
    T randomNumberWithinRange(const T &first, const T &second)
    {
        std::uniform_int_distribution<T> distribution(first, second);

        return distribution(generator);
    }

public:
    static void random(ListGraph &listg, MatrixGraph &matrixg, size_t count, size_t fillFactor)
    {
        
    }
};