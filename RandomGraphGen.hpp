#pragma once

#include <random>

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"

static std::random_device rd;
static std::default_random_engine generator(rd());

class RandomGraphGen {
    const static size_t MAX_WEIGHT;

    static size_t randomNumberWithinRange(const size_t &first, const size_t &second)
    {
        std::uniform_int_distribution<size_t> distribution(first, second);

        return distribution(generator);
    }

public:
    template <typename Container>
    static void random(Container &graph, size_t vertexCount, size_t fillFactor, const bool &isDirected = true)
    {
        size_t edgesCount;

        edgesCount = vertexCount * (vertexCount - 1);

        // Not directed graphs have two times less edges
        if (!isDirected)
            edgesCount /= 2;

        edgesCount *= 0.01 * fillFactor;

        for (; edgesCount > 0; edgesCount--) {
            size_t from = randomNumberWithinRange(0, vertexCount - 1);
            size_t to = randomNumberWithinRange(0, vertexCount - 1);
            size_t weight = randomNumberWithinRange(1, MAX_WEIGHT);

            graph.addEdge(from, to, weight);
        }
    }

    static void random(ListGraph &listg, MatrixGraph &matrixg, size_t vertexCount, size_t fillFactor, const bool &isDirected = true)
    {
        size_t edgesCount;

        edgesCount = vertexCount * (vertexCount - 1);

        if (!isDirected)
            edgesCount /= 2;

        edgesCount *= 0.01 * fillFactor;

        for (; edgesCount > 0; edgesCount--) {
            size_t from = randomNumberWithinRange(0, vertexCount - 1);
            size_t to = randomNumberWithinRange(0, vertexCount - 1);
            size_t weight = randomNumberWithinRange(1, 99);

            listg.addEdge(from, to, weight);
            matrixg.addEdge(from, to, weight);
        }
    }
};

const size_t RandomGraphGen::MAX_WEIGHT = INT16_MAX;