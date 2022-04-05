#pragma once

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "MinHeap.hpp"

class Prima {

public:
    //void addAllEdgesOfVertex()
    static ListGraph *generateMst(const ListGraph &graph)
    {
        auto &edges = graph.getEdges();
        auto &vertices = graph.getVertexCount();

        ListGraph *mst = new ListGraph();

        Array<bool> seenVertices(vertices);
        MinHeap<const ListGraph::Edge *> edgesQueue;
        seenVertices[0] = true;

        size_t curVertex = 0;
        for (size_t addedEdges = 0; addedEdges < vertices - 1; addedEdges++) {
            for (size_t i = 0; i < edges.size(); i++) {
                const ListGraph::Edge *candidate = nullptr;
                
                if (edges[i].to == curVertex)
                    if(!seenVertices[edges[i].from])
                        candidate = &edges[i];
                if (edges[i].from == curVertex)
                    if (!seenVertices[edges[i].to])
                        candidate = &edges[i];

                if (candidate)
                    edgesQueue.push(candidate);
            }

            curVertex++;
        }
    }
};