#pragma once

#include "Array.hpp"
#include "MinHeap.hpp"

class Dijkstra {

    struct PathNode {
        size_t weight = SIZE_MAX;
        size_t prev = SIZE_MAX;

        PathNode(const size_t weight, const size_t &prev) : weight(weight), prev(prev) { };
        PathNode() { };
    };

public:
    struct DijkstraResult {
        size_t totalCost;
        Array<size_t> path;
    };

    static DijkstraResult *getShortestPath(const ListGraph &graph, const size_t &from, const size_t &to)
    {
        DijkstraResult *result = new DijkstraResult();
        if (from == to) {
            result->totalCost = 0;
            result->path.push_back(from);
            return result;
        }

        auto &edges = graph.getEdges();
        auto &vertices = graph.getVertexCount();

        MinHeap<size_t> vertexToProcess;
        Array<PathNode> pathWeights(edges.size() + 1); //FIXME

        vertexToProcess.push(from);
        pathWeights[from].weight = 0;

        while (!vertexToProcess.empty()) {
            auto curVertex = vertexToProcess.top();

            if (curVertex == to)
                break;
            vertexToProcess.pop();

            for (size_t i = 0; i < edges.size(); i++) {
                auto newVertex = edges[i].to;
                if (edges[i].from == curVertex) {
                    if (pathWeights[newVertex].weight > pathWeights[curVertex].weight + edges[i].weight) {
                        pathWeights[newVertex].weight = pathWeights[curVertex].weight + edges[i].weight;
                        pathWeights[newVertex].prev = curVertex;
                        vertexToProcess.push(newVertex);
                    }
                }
            }
        }

        result->totalCost = pathWeights[to].weight;
        auto cur = to;
        while (cur != from)
        {
            result->path.push_front(cur);
            cur = pathWeights[cur].prev;
        }
        result->path.push_front(from);

        return result;
    }
};