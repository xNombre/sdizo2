#pragma once

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "MinHeap.hpp"

class Prima {

public:
    static ListGraph *generateMst(const ListGraph &graph)
    {
        auto &edges = graph.getEdges();
        auto &vertices = graph.getVertexCount();

        ListGraph *mst = new ListGraph();

        Array<bool> seenVertices(vertices);
        MinHeap<ListGraph::Edge> edgesQueue;
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
        for (size_t addedEdges = 0; addedEdges < vertices - 1; addedEdges++) {
            ListGraph::Edge candidate = edgesQueue.top();
            edgesQueue.pop();

            if (!seenVertices[candidate.to]) {
                curVertex = candidate.to;
                seenVertices[curVertex] = true;
                mst->addEdge(candidate);

                pushAdjacentEdges();
            }
            else if (!seenVertices[candidate.from]) {
                curVertex = candidate.from;
                seenVertices[curVertex] = true;
                mst->addEdge(candidate);

                pushAdjacentEdges();
            }
        }

        return mst;
    }

    static MatrixGraph generateMst(const MatrixGraph &graph)
    {
        const auto &edges = graph.getEdgesCount();
        const auto &vertices = graph.getVertexCount();
        const auto &matrix = graph.getMatrix();

        MatrixGraph mst;

        Array<bool> seenVertices(vertices);
        MinHeap<ListGraph::Edge> edgesQueue;
        size_t curVertex;

        // Pushes all edges adjacent to curVertex onto min heap
        auto pushAdjacentEdges = [&]() {
            for (size_t i = 0; i < edges; i++) {
                // Find edges adjacent to curVertex
                if (matrix[curVertex][i] == 0)
                    continue;

                for (size_t end = 0; end < edges; end++) {
                    // Find end vertices of edges adjacent to curVertex
                    if (matrix[end][i] == 0)
                        continue;

                    // Queue edge if vertex not visited yet
                    if (end != curVertex && !seenVertices[end]) {
                        edgesQueue.push(
                            ListGraph::Edge(curVertex, end, std::abs(matrix[end][i]))
                        );
                    }
                }

            }
        };

        // Start from vertex 0
        seenVertices[0] = true;
        curVertex = 0;
        pushAdjacentEdges();

        // MST will always have (vertices - 1) edges
        for (size_t addedEdges = 0; addedEdges < vertices - 1; addedEdges++) {
            ListGraph::Edge candidate = edgesQueue.top();
            edgesQueue.pop();

            if (!seenVertices[candidate.to]) {
                curVertex = candidate.to;
                seenVertices[curVertex] = true;
                mst.addEdge(candidate.from, candidate.to, candidate.weight);

                pushAdjacentEdges();
            }
            else if (!seenVertices[candidate.from]) {
                curVertex = candidate.from;
                seenVertices[curVertex] = true;
                mst.addEdge(candidate.from, candidate.to, candidate.weight);

                pushAdjacentEdges();
            }
        }

        return mst;
    }

};