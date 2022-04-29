#pragma once

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "MinHeap.hpp"

class Prima {

public:
    static ListGraph generateMst(const ListGraph &graph)
    {
        const auto &edges = graph.getEdges();
        const auto &vertices = graph.getVertexCount();

        ListGraph mst;

        if (vertices == 0)
            return mst;

        Array<bool> seenVertices(vertices);
        MinHeap<Edge> edgesQueue;
        size_t curVertex;

        // Pushes all edges adjacent to curVertex onto min heap
        // This needs to be done for to and from because ListGraph
        // isn't bidirectional
        auto pushAdjacentEdges = [&]() {
            for (size_t i = 0; i < edges.size(); i++) {
                if (edges[i].to == curVertex) {
                    if (!seenVertices[edges[i].from])
                        edgesQueue.push(edges[i]);
                }
                else if (edges[i].from == curVertex) {
                    if (!seenVertices[edges[i].to])
                        edgesQueue.push(edges[i]);
                }
            }
        };

        // Start from vertex 0
        seenVertices[0] = true;
        curVertex = 0;
        pushAdjacentEdges();

        // MST will always have (vertices - 1) edges
        for (size_t addedEdges = 0; addedEdges < vertices - 1; ) {
            Edge candidate = edgesQueue.top();
            edgesQueue.pop();

            if (!seenVertices[candidate.to]) {
                curVertex = candidate.to;
                seenVertices[curVertex] = true;
                mst.addEdge(candidate);

                pushAdjacentEdges();
                addedEdges++;
            }
            else if (!seenVertices[candidate.from]) {
                curVertex = candidate.from;
                seenVertices[curVertex] = true;
                mst.addEdge(candidate);

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
            for (size_t i = 0; i < edges; i++) {
                // Find edges adjacent to curVertex
                if (matrix[curVertex][i] == 0)
                    continue;

                for (size_t endVertex = 0; endVertex < vertices; endVertex++) {
                    // Find end vertice of adjacent edge

                    if (matrix[endVertex][i] == 0 || endVertex == curVertex)
                        continue;

                    // Queue edge if vertex not visited yet
                    if (seenVertices[endVertex])
                        continue;

                    edgesQueue.push(
                        Edge(curVertex, endVertex, std::abs(matrix[endVertex][i]))
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