#pragma once

#include "Array.hpp"
#include "MinHeap.hpp"
#include "MatrixGraph.hpp"

class Dijkstra {

    struct PathNode {
        size_t weight = SIZE_MAX;
        size_t prev;

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

        MinHeap<size_t> vertexToProcess;
        Array<PathNode> pathWeights(graph.getVertexCount());

        vertexToProcess.push(from);
        pathWeights[from].weight = 0;

        while (!vertexToProcess.empty()) {
            auto curVertex = vertexToProcess.top();
            vertexToProcess.pop();

            for (size_t i = 0; i < edges.size(); i++) {
                auto newVertex = edges[i].to;

                // Find all edges adjacent to curVertex
                if (edges[i].from != curVertex)
                    continue;

                // Look for shorter path
                if (pathWeights[newVertex].weight >
                    pathWeights[curVertex].weight + edges[i].weight) {
                    // Update path weight
                    pathWeights[newVertex].weight =
                        pathWeights[curVertex].weight + edges[i].weight;

                    // Save previous vertex to be able to restore the shortest path
                    pathWeights[newVertex].prev = curVertex;

                    // Recalculate path weights for newVertex
                    vertexToProcess.push(newVertex);
                }
            }
        }

        // Prepare result and return
        result->totalCost = pathWeights[to].weight;
        auto cur = to;
        while (cur != from) {
            result->path.push_front(cur);
            cur = pathWeights[cur].prev;
        }
        result->path.push_front(from);

        return result;
    }

    static DijkstraResult *getShortestPath(const MatrixGraph &graph, const size_t &from, const size_t &to)
    {
        DijkstraResult *result = new DijkstraResult();
        if (from == to) {
            result->totalCost = 0;
            result->path.push_back(from);
            return result;
        }

        // Prepare result and return
        //result->totalCost = pathWeights[to].weight;
        auto cur = to;
        while (cur != from) {
            result->path.push_front(cur);
            //cur = pathWeights[cur].prev;
        }
        result->path.push_front(from);

        return result;
    }
};