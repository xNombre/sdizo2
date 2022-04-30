#pragma once

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "MinHeap.hpp"

class Prima {

public:
    static ListGraph generateMst(const ListGraph &graph)
    {
        //const auto &edges = graph.getEdges();
        const auto &vertices = graph.getVertexCount();

        ListGraph mst(false);

        if (vertices == 0)
            return mst;

        Array<bool> seenVertices(vertices);
        MinHeap<Edge> edgesQueue;
        size_t curVertex;

        // Pushes all edges adjacent to curVertex onto min heap
        auto pushAdjacentEdges = [&]() {
            const auto &adjacent = graph.getVerticesAdjacentTo(curVertex);
            for (size_t i = 0; i < adjacent.size(); i++) {
                // curVertex won't be queued because it is already marged as visited
                if (!seenVertices[adjacent[i].edge])
                        edgesQueue.push(Edge(curVertex, adjacent[i].edge, adjacent[i].weight));
            }
        };

        // Start from vertex 0
        seenVertices[0] = true;
        curVertex = 0;
        pushAdjacentEdges();

        // MST will always have (vertices - 1) edges
        for (size_t addedEdges = 0; addedEdges < vertices - 1; ) {
            if (edgesQueue.empty()) {
                mst = ListGraph(false);
                break;
            }
            
            Edge candidate = edgesQueue.top();
            edgesQueue.pop();

            if (!seenVertices[candidate.to]) {
                curVertex = candidate.to;
                seenVertices[curVertex] = true;
                mst.addEdge(candidate.from, candidate.to, candidate.weight);

                pushAdjacentEdges();
                addedEdges++;
            }
        }

        return mst;
    }

    static MatrixGraph generateMst(const MatrixGraph &graph)
    {
        const auto &edges = graph.getEdgesCount();
        const auto &vertices = graph.getVertexCount();
        const auto &matrix = graph.getMatrix();

        MatrixGraph mst(false);

        if (vertices == 0)
            return mst;

        Array<bool> seenVertices(vertices);
        MinHeap<Edge> edgesQueue;
        size_t curVertex;

        // Pushes all edges adjacent to curVertex onto min heap
        auto pushAdjacentEdges = [&]() {
            for (size_t edge = 0; edge < edges; edge++) {
                // Find edges adjacent to curVertex
                if (matrix[curVertex][edge] == 0)
                    continue;

                for (size_t endVertex = 0; endVertex < vertices; endVertex++) {
                    // Find end vertice of adjacent edge

                    if (matrix[endVertex][edge] == 0 || endVertex == curVertex)
                        continue;

                    // Queue edge if vertex not visited yet
                    if (seenVertices[endVertex])
                        continue;

                    edgesQueue.push(
                        Edge(curVertex, endVertex, matrix[endVertex][edge])
                    );
                }
            }
        };

        // Start from vertex 0
        seenVertices[0] = true;
        curVertex = 0;
        pushAdjacentEdges();

        // MST will always have (vertices - 1) edges
        for (size_t addedEdges = 0; addedEdges < vertices - 1; ) {
            if (edgesQueue.empty()) {
                mst = MatrixGraph(false);
                break;
            }
            
            Edge candidate = edgesQueue.top();
            edgesQueue.pop();

            if (!seenVertices[candidate.to]) {
                curVertex = candidate.to;
                seenVertices[curVertex] = true;
                mst.addEdge(candidate.from, candidate.to, candidate.weight);

                pushAdjacentEdges();
                addedEdges++;
            }
        }

        return mst;
    }

};