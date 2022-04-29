#pragma once

#include <random>

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"

static std::random_device rd;
static std::default_random_engine generator(rd());

class RandomGraphGen {
    static size_t randomNumberWithinRange(const size_t &first, const size_t &second)
    {
        std::uniform_int_distribution<size_t> distribution(first, second);

        return distribution(generator);
    }

public:
    static void random(ListGraph &listg, MatrixGraph &matrixg, size_t vertexCount, size_t fillFactor, const bool &isDirected = true)
    {
        size_t edgesCount;

        edgesCount = vertexCount * (vertexCount - 1);

        if (isDirected)
            edgesCount /= 2;

        edgesCount *= 0.01 * fillFactor;

        for (; edgesCount > 0; edgesCount--) {
            size_t from = randomNumberWithinRange(0, vertexCount - 1);
            size_t to = randomNumberWithinRange(0, vertexCount - 1);
            size_t weight = randomNumberWithinRange(1, 100);

            listg.addEdge(from, to, weight);
            matrixg.addEdge(from, to, weight);
        }
    }

    template <typename Container>
    static void random(Container &graph, size_t vertexCount, size_t fillFactor, const bool &isDirected = true)
    {
        size_t edgesCount;

        edgesCount = vertexCount * (vertexCount - 1);

        if (isDirected)
            edgesCount /= 2;

        edgesCount *= 0.01 * fillFactor;

        for (; edgesCount > 0; edgesCount--) {
            size_t from = randomNumberWithinRange(0, vertexCount - 1);
            size_t to = randomNumberWithinRange(0, vertexCount - 1);
            size_t weight = randomNumberWithinRange(1, INT32_MAX);

            graph.addEdge(from, to, weight);
        }
    }
};