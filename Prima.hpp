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

        Array<bool> seenVertices(vertices+1);
        MinHeap<ListGraph::Edge> edgesQueue;
        seenVertices[1] = true;

        size_t curVertex = 1;
        for (size_t i = 0; i < edges.size(); i++) {
            const ListGraph::Edge *candidate = nullptr;

            if (edges[i].to == curVertex)
                if (!seenVertices[edges[i].from])
                    candidate = &edges[i];
            if (edges[i].from == curVertex)
                if (!seenVertices[edges[i].to])
                    candidate = &edges[i];

            if (candidate)
                edgesQueue.push(*candidate);
        }

        for (size_t addedEdges = 0; addedEdges < vertices - 1; addedEdges++) {
            ListGraph::Edge candidate;
            candidate = edgesQueue.top();
            edgesQueue.pop();

            if (!seenVertices[candidate.to]) {
                curVertex = candidate.to;
                seenVertices[curVertex] = true;
                mst->addEdge(candidate);

                for (size_t i = 0; i < edges.size(); i++) {
                    const ListGraph::Edge *candidate = nullptr;

                    if (edges[i].to == curVertex) {
                        if (!seenVertices[edges[i].from])
                            candidate = &edges[i];
                    }
                    else if (edges[i].from == curVertex)
                        if (!seenVertices[edges[i].to])
                            candidate = &edges[i];

                    if (candidate)
                        edgesQueue.push(*candidate);
                }
            }
            else if (!seenVertices[candidate.from]) {
                curVertex = candidate.from;
                seenVertices[curVertex] = true;
                mst->addEdge(candidate);

                for (size_t i = 0; i < edges.size(); i++) {
                    const ListGraph::Edge *candidate = nullptr;

                    if (edges[i].to == curVertex)
                        if (!seenVertices[edges[i].from])
                            candidate = &edges[i];
                        else if (edges[i].from == curVertex)
                            if (!seenVertices[edges[i].to])
                                candidate = &edges[i];

                    if (candidate)
                        edgesQueue.push(*candidate);
                }
            }
        }
        
        return mst;
    }
};