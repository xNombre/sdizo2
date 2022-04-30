#pragma once

#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "TotalPathCost.hpp"
#include "PathNode.hpp"

class BellmanFord {

public:
    static Array<PathNode> getShortestPath(const ListGraph &graph, const size_t &from = 0)
    {
        const auto &vertices = graph.getVertexCount();

        Array<PathNode> pathWeights(vertices);

        if (vertices == 0)
            return pathWeights;

        pathWeights[from].weight = 0;
        bool changesMade;

        for (size_t i = 0; i < vertices - 1; i++) {
            changesMade = false;

            for (size_t vertex = 0; vertex < vertices; vertex++) {
                // Skip vertices that are not visited yet
                if (pathWeights[vertex].weight == SIZE_MAX)
                    continue;

                const auto &adjacent = graph.getVerticesAdjacentTo(vertex);
                for (size_t edge = 0; edge < adjacent.size(); edge++) {
                    const auto &curEdgeTo = adjacent[edge].edge;
                    const auto &weight = adjacent[edge].weight;

                    // Check whether path can be shorter
                    if (pathWeights[curEdgeTo].weight >
                        pathWeights[vertex].weight + weight) {
                        // Update path weight
                        pathWeights[curEdgeTo].weight =
                            pathWeights[vertex].weight + weight;

                        // Save previous vertex
                        pathWeights[curEdgeTo].prev = vertex;

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

        Array<PathNode> pathWeights(vertices);

        if (vertices == 0)
            return pathWeights;

        pathWeights[from].weight = 0;
        bool changesMade;

        for (size_t i = 0; i < vertices - 1; i++) {
            changesMade = false;

            for (size_t vertex = 0; vertex < vertices; vertex++) {
                // Skip vertices that are not visited yet
                if (pathWeights[vertex].weight == SIZE_MAX)
                    continue;

                // Find edges coming out for vertex
                for (size_t edge = 0; edge < edges; edge++) {
                    size_t curEdgeFrom, curEdgeTo, weight;

                    if (matrix[vertex][edge] >= 0)
                        continue;

                    if (matrix[vertex][edge] < 0) {
                        curEdgeFrom = vertex;

                        // Now find destination vertex 
                        for (size_t i = 0; i < vertices; i++) {
                            if (matrix[i][edge] > 0)
                                curEdgeTo = i;
                        }

                        weight = matrix[curEdgeTo][edge];
                    }

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