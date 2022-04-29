#pragma once

#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "TotalPathCost.hpp"

class BellmanFord {
    struct PathNode {
        size_t weight = SIZE_MAX;
        size_t prev = SIZE_MAX;

        PathNode(const size_t weight, const size_t &prev) : weight(weight), prev(prev) { };
        PathNode() { };
    };

public:
    static Array<PathNode> getShortestPath(const ListGraph &graph, const size_t &from = 0)
    {
        const auto &edges = graph.getEdges();
        const auto &vertices = graph.getVertexCount();

        Array<PathNode> pathWeights(edges.size());
        pathWeights[from].weight = 0;

        bool changesMade;

        for (size_t i = 0; i < vertices; i++) {
            changesMade = false;

            for (size_t vertex = 0; vertex <= vertices; vertex++) {
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

        return pathWeights;
    }

    static Array<PathNode> getShortestPath(const MatrixGraph &graph, const size_t &from = 0)
    {
        const auto &matrix = graph.getMatrix();
        const auto &edges = graph.getEdgesCount();
        const auto &vertices = graph.getVertexCount();

        Array<PathNode> pathWeights(edges);
        pathWeights[from].weight = 0;

        bool changesMade;

        for (size_t i = 0; i < vertices; i++) {
            changesMade = false;

            for (size_t edge = 0; edge < edges; edge++) {
                bool fromEdgeSet = false;
                size_t curEdgeFrom, curEdgeTo, weight;

                for (size_t vertex = 0; vertex < vertices; vertex++) {
                    if (matrix[vertex][edge] > 0) {
                        curEdgeTo = vertex;
                        weight = matrix[vertex][edge];
                    }
                    else if (matrix[vertex][edge] < 0) {
                        curEdgeFrom = vertex;
                        fromEdgeSet = true;
                    }
                }

                if (!fromEdgeSet)
                    continue;

                // Skip vertices that are not visited yet
                if (pathWeights[curEdgeFrom].weight == SIZE_MAX)
                    continue;

                // Check whether path can be shorter
                if (pathWeights[curEdgeTo].weight >
                    pathWeights[curEdgeFrom].weight + weight) {
                    // Update path weight
                    pathWeights[curEdgeTo].weight =
                        pathWeights[curEdgeFrom].weight + weight;

                    pathWeights[curEdgeTo].prev = curEdgeFrom;
                    changesMade = true;
                }

            }

            // Break early if no changes were made
            // This is ok per algorithm documentation
            if (!changesMade)
                break;
        }

        return pathWeights;
    }

    template<typename T>
    static TotalPathCost getShortestPathFromTo(const T &graph, const size_t &from, const size_t &to)
    {
        TotalPathCost result;

        if (graph.getVertexCount() == 0)
            return result;

        if (graph.getVertexCount() < std::max(from, to) + 1)
            return result;

        auto pathWeights = getShortestPath(graph, from);

        // There can be no path
        if (pathWeights[to].weight == SIZE_MAX)
            return result;

        result.totalCost = pathWeights[to].weight;

        auto cur = to;
        while (cur != from) {
            result.path.push_front(cur);
            cur = pathWeights[cur].prev;
        }
        result.path.push_front(from);

        return result;
    }
};