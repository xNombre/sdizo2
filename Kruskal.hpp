#pragma once

#include "UnionFind.hpp"
#include "MinHeap.hpp"

#include "ListGraph.hpp"
#include "MatrixGraph.hpp"

using std::size_t;

class Kruskal {

public:

    static ListGraph *generateMst(const ListGraph &graph)
    {
        auto &edges = graph.getEdges();
        auto &vertices = graph.getVertexCount();
        ListGraph *mstGraph = new ListGraph();

        UnionFind forest(vertices);
        MinHeap<ListGraph::Edge> edgesQueue;

        for (size_t i = 0; i < edges.size(); i++) {
            edgesQueue.push(edges[i]);
        }

        size_t addedEdges = 0;

        // Minimal edges needed to create mst is vertices - 1
        while (addedEdges < vertices - 1) {
            const auto &node = edgesQueue.top();

            auto &aParent = forest.findNode(node.from);
            auto &bParent = forest.findNode(node.to);

            if (aParent != bParent) {
                // Vertices not connected, union em
                forest.unionNodes(node.from, node.to);
                mstGraph->addEdge(node.from, node.to, node.weight);
            }
            
            edgesQueue.pop();
            
            addedEdges++;
        }

        return mstGraph;
    }

    static MatrixGraph *generateMst(const MatrixGraph &graph)
    {
        auto &vertices = graph.getVertexCount();
        MatrixGraph *mstGraph = new MatrixGraph();
    }
};