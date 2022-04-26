#pragma once

#include "Array.hpp"
#include "MinHeap.hpp"
#include "MatrixGraph.hpp"
#include "TotalPathCost.hpp"

class Dijkstra {

    struct PathNode {
        size_t weight = SIZE_MAX;
        size_t prev;

        PathNode(const size_t weight, const size_t &prev) : weight(weight), prev(prev) { };
        PathNode() { };
    };

    struct HeapNode {
        size_t distance;
        size_t vertex;

        bool operator> (const HeapNode &other) const
        {
            return distance > other.distance;
        }
        bool operator< (const HeapNode &other) const
        {
            return distance < other.distance;
        }

        HeapNode(const size_t &vertex, const size_t &distance) :
            distance(distance), vertex(vertex)
        {
        }

        HeapNode()
        {
        }
    };

public:
    static TotalPathCost getShortestPath(const ListGraph &graph, const size_t &from, const size_t &to)
    {
        TotalPathCost result;
        if (from == to) {
            result.totalCost = 0;
            result.path.push_back(from);
            return result;
        }

        const auto &edges = graph.getEdges();

        MinHeap<HeapNode> vertexToProcess;
        Array<PathNode> pathWeights(graph.getVertexCount());

        vertexToProcess.push(HeapNode(from, 0));
        pathWeights[from].weight = 0;

        while (!vertexToProcess.empty()) {
            auto node = vertexToProcess.top();
            auto curVertex = node.vertex;
            vertexToProcess.pop();

            // Check if shorter path has been already processed
            if (node.distance != pathWeights[curVertex].weight)
                continue;

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
                    vertexToProcess.push(HeapNode(newVertex, pathWeights[newVertex].weight));
                }
            }
        }

        // Prepare result and return
        result.totalCost = pathWeights[to].weight;
        auto cur = to;
        while (cur != from) {
            result.path.push_front(cur);
            cur = pathWeights[cur].prev;
        }
        result.path.push_front(from);

        return result;
    }

    static TotalPathCost getShortestPath(const MatrixGraph &graph, const size_t &from, const size_t &to)
    {
        TotalPathCost result;
        if (from == to) {
            result.totalCost = 0;
            result.path.push_back(from);
            return result;
        }

        const auto &matrix = graph.getMatrix();
        const auto &edges = graph.getEdgesCount();
        const auto &vertices = graph.getVertexCount();

        MinHeap<HeapNode> vertexToProcess;
        Array<PathNode> pathWeights(vertices);

        vertexToProcess.push(HeapNode(from, 0));
        pathWeights[from].weight = 0;

        while (!vertexToProcess.empty()) {
            auto node = vertexToProcess.top();
            auto curVertex = node.vertex;
            vertexToProcess.pop();

            // Check if shorter path has been already processed
            if (node.distance != pathWeights[curVertex].weight)
                continue;

            // Pushes all edges adjacent to curVertex onto min heap
            for (size_t i = 0; i < edges; i++) {
                // Find edges adjacent to curVertex
                if (matrix[curVertex][i] == 0)
                    continue;

                for (size_t endVertex = 0; endVertex < vertices; endVertex++) {
                    // Find end vertice of adjacent edge

                    if (matrix[endVertex][i] == 0 || endVertex == curVertex)
                        continue;

                    // Look for shorter path
                    if (pathWeights[endVertex].weight >
                        pathWeights[curVertex].weight + matrix[endVertex][i]) {
                        // Update path weight
                        pathWeights[endVertex].weight =
                            pathWeights[curVertex].weight + matrix[endVertex][i];

                        // Save previous vertex to be able to restore the shortest path
                        pathWeights[endVertex].prev = curVertex;

                        // Recalculate path weights for endVertex
                        vertexToProcess.push(HeapNode(endVertex, pathWeights[endVertex].weight));
                    }
                }
            }
        }

        // Prepare result and return
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