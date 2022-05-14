#include "RandomGraphGen.hpp"
#include <map>
#include <vector>

const size_t RandomGraphGen::MAX_WEIGHT = INT16_MAX;

size_t RandomGraphGen::randomNumberWithinRange(const size_t &first, const size_t &second)
{
    std::uniform_int_distribution<size_t> distribution(first, second);

    return distribution(generator);
}

template <typename Container>
void RandomGraphGen::random(Container &graph, size_t vertexCount, size_t fillFactor, const bool &isDirected)
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

template void RandomGraphGen::random(ListGraph &graph,
                                     size_t vertexCount,
                                     size_t fillFactor,
                                     const bool &isDirected);
template void RandomGraphGen::random(MatrixGraph &graph,
                                     size_t vertexCount,
                                     size_t fillFactor,
                                     const bool &isDirected);

void RandomGraphGen::random(ListGraph &listg, MatrixGraph &matrixg, size_t vertexCount, size_t fillFactor,
                            const bool &isDirected)
{
    size_t edgesCount;

    if (fillFactor > 100)
        throw new std::invalid_argument("fillFactor can't be greater than 100");

    edgesCount = vertexCount * (vertexCount - 1);

    if (!isDirected)
        edgesCount /= 2;

    edgesCount *= 0.01 * fillFactor;

    if (!isDirected && edgesCount >= vertexCount - 1) {
        std::vector<bool> seen(vertexCount, false);
        seen[0] = true;
        for (size_t i = 1; i < vertexCount - 1; ++i) {
            if (seen[i] != true) {
                size_t already_connected = randomNumberWithinRange(0, vertexCount - 1);;
                while (seen[already_connected] != true)
                    already_connected = randomNumberWithinRange(0, vertexCount - 1);
                seen[i] = true;
                size_t weight = randomNumberWithinRange(1, 99);
                listg.addEdge(already_connected, i, weight);
                matrixg.addEdge(already_connected, i, weight);
            }
        }
        edgesCount -= vertexCount - 1;
    }
    
    for (; edgesCount > 0; edgesCount--) {
        size_t from = randomNumberWithinRange(0, vertexCount - 1);
        size_t to = randomNumberWithinRange(0, vertexCount - 1);
        size_t weight = randomNumberWithinRange(1, 99);

        listg.addEdge(from, to, weight);
        matrixg.addEdge(from, to, weight);
    }
}
