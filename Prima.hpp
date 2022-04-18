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

    static MatrixGraph *generateMst(const MatrixGraph &graph)
    {
        //return mst;
    }

};