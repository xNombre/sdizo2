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
        auto &edges = graph.getEdges();

        Array<PathNode> pathWeights(edges.size() + 1); //FIXME
        pathWeights[1].weight = 0;

        bool changesMade = false;
        do {
            changesMade = false;
            for (size_t vertex = 1; vertex <= graph.getVertexCount(); vertex++) {
                for (size_t edge = 0; edge < edges.size(); edge++) {
                    // Skip vertices that are not visited yet
                    if (pathWeights[edges[edge].from].weight != SIZE_MAX &&
                        edges[edge].from == vertex) {
                        if (pathWeights[edges[edge].to].weight >
                            pathWeights[edges[edge].from].weight + edges[edge].weight) {
                            changesMade = true;
                            pathWeights[edges[edge].to].weight = pathWeights[edges[edge].from].weight + edges[edge].weight;
                            pathWeights[edges[edge].to].prev = edges[edge].from;
                        }
                    }
                }

            }
            
        } while (changesMade);
    }
};