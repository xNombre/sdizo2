#pragma once

#include <random>

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"

static std::random_device rd;
static std::default_random_engine generator(rd());

class RandomGraphGen {
    const static size_t MAX_WEIGHT;

    static size_t randomNumberWithinRange(const size_t &first, const size_t &second);

public:
    template <typename Container>
    static void random(Container &graph, size_t vertexCount, size_t fillFactor,
                       const bool &isDirected = true);

    static void random(ListGraph &listg, MatrixGraph &matrixg, size_t vertexCount,
                       size_t fillFactor, const bool &isDirected = true);
};