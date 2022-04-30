#pragma once

#include "Array.hpp"
#include "MinHeap.hpp"
#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "TotalPathCost.hpp"
#include "PathNode.hpp"
class Dijkstra {
    struct HeapNode {
        size_t distance;
        size_t vertex;

        bool operator>(const HeapNode &other) const
        {
            return distance > other.distance;
        }
        bool operator<(const HeapNode &other) const
        {
            return distance < other.distance;
        }

        HeapNode(const size_t &vertex, const size_t &distance) :
            distance(distance), vertex(vertex)
        {
        }

        HeapNode() { }
    };

public:
    static Array<PathNode> getShortestPath(const ListGraph &graph, const size_t &from = 0)
    {
        const auto &vertices = graph.getVertexCount();

        MinHeap<HeapNode> vertexToProcess;
        Array<PathNode> pathWeights(vertices);

        if (vertices == 0)
            return pathWeights;

        vertexToProcess.push(HeapNode(from, 0));
        pathWeights[from].weight = 0;
        pathWeights[from].prev = SIZE_MAX;

        while (!vertexToProcess.empty()) {
            const auto node = vertexToProcess.top();
            const auto &curVertex = node.vertex;
            vertexToProcess.pop();

            // Check if shorter path has been already processed
            // https://cs.stackexchange.com/questions/118388/dijkstra-without-decrease-key
            if (node.distance != pathWeights[curVertex].weight)
                continue;

            const auto &adjacent = graph.getVerticesAdjacentTo(curVertex);
            for (size_t i = 0; i < adjacent.size(); i++) {
                const auto &newVertex = adjacent[i].edge;

                // Look for shorter path
                if (pathWeights[newVertex].weight >
                    pathWeights[curVertex].weight + adjacent[i].weight) {
                    // Update path weight
                    pathWeights[newVertex].weight =
                        pathWeights[curVertex].weight + adjacent[i].weight;

                    // Save previous vertex to be able to restore the shortest path
                    pathWeights[newVertex].prev = curVertex;

                    // Recalculate path weights for newVertex
                    vertexToProcess.push(HeapNode(newVertex, pathWeights[newVertex].weight));
                }
            }
        }

        return pathWeights;
    }

    static Array<PathNode> getShortestPath(const MatrixGraph &graph, const size_t &from = 0)
    {
        const auto &matrix = graph.getMatrix();
        const auto &edges = graph.getEdgesCount();
        const auto &vertices = graph.getVertexCount();

        MinHeap<HeapNode> vertexToProcess;
        Array<PathNode> pathWeights(vertices);

        if (vertices == 0)
            return pathWeights;

        vertexToProcess.push(HeapNode(from, 0));
        pathWeights[from].weight = 0;

        while (!vertexToProcess.empty()) {
            const auto node = vertexToProcess.top();
            const auto &curVertex = node.vertex;
            vertexToProcess.pop();

            // Check if shorter path has been already processed
            if (node.distance != pathWeights[curVertex].weight)
                continue;

            // Pushes all edges adjacent to curVertex onto min heap
            for (size_t edge = 0; edge < edges; edge++) {
                // Find edges coming from curVertex
                if (matrix[curVertex][edge] >= 0)
                    continue;

                for (size_t endVertex = 0; endVertex < vertices; endVertex++) {
                    // Find end vertex of adjacent edge
                    if (matrix[endVertex][edge] <= 0)
                        continue;

                    // Look for shorter path
                    if (pathWeights[endVertex].weight >
                        pathWeights[curVertex].weight + matrix[endVertex][edge]) {
                        // Update path weight
                        pathWeights[endVertex].weight =
                            pathWeights[curVertex].weight + matrix[endVertex][edge];

                        // Save previous vertex to be able to restore the shortest path
                        pathWeights[endVertex].prev = curVertex;

                        // Recalculate path weights for endVertex
                        vertexToProcess.push(HeapNode(endVertex, pathWeights[endVertex].weight));
                    }
                }
            }
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