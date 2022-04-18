#pragma once

#include "ListGraph.hpp"

class BellmanFord {
    struct PathNode {
        size_t weight = SIZE_MAX;
        size_t prev = SIZE_MAX;

        PathNode(const size_t weight, const size_t &prev) : weight(weight), prev(prev) { };
        PathNode() { };
    };

public:
    struct BellmanFordResult {
        size_t totalCost;
        Array<size_t> path;
    };

    static BellmanFordResult *getShortestPath(const ListGraph &graph, const size_t &from, const size_t &to)
    {
        BellmanFordResult *result = new BellmanFordResult();
        if (from == to) {
            result->totalCost = 0;
            result->path.push_back(from);
            return result;
        }

        auto &edges = graph.getEdges();

        Array<PathNode> pathWeights(edges.size());
        pathWeights[0].weight = 0;

        bool changesMade;

        for (size_t i = 0; i < graph.getVertexCount(); i++) {
            changesMade = false;

            for (size_t vertex = 0; vertex <= graph.getVertexCount(); vertex++) {
                for (size_t edge = 0; edge < edges.size(); edge++) {
                    const auto &curEdge = edges[edge];

                    if (curEdge.from != vertex)
                        continue;

                    // Skip vertices that are not visited yet
                    if (pathWeights[curEdge.from].weight == SIZE_MAX)
                        continue;

                    // Check whether path can be shorter
                    if (pathWeights[curEdge.to].weight >
                        pathWeights[curEdge.from].weight + curEdge.weight) {
                        // Update path weight
                        pathWeights[curEdge.to].weight =
                            pathWeights[curEdge.from].weight + curEdge.weight;

                        pathWeights[curEdge.to].prev = curEdge.from;
                        changesMade = true;
                    }
                }
            }

            // Break early if no changes were made
            // This is ok per algorithm documentation
            if (!changesMade)
                break;
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

    static BellmanFordResult *getShortestPath(const MatrixGraph &graph, const size_t &from, const size_t &to)
    {
        BellmanFordResult *result = new BellmanFordResult();
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