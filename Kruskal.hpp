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

        // Push all edges to the heap
        for (size_t i = 0; i < edges.size(); i++) {
            edgesQueue.push(edges[i]);
        }

        // MST will always have (vertices - 1) edges
        for (size_t addedEdges = 0; addedEdges < vertices - 1; addedEdges++) {
            const auto &node = edgesQueue.top();

            auto &aParent = forest.findNode(node.from);
            auto &bParent = forest.findNode(node.to);

            if (aParent != bParent) {
                // Vertices not connected, union em
                forest.unionNodes(node.from, node.to);
                // Edge needs to be reprocessed
                mstGraph->addEdge(node.from, node.to, node.weight);
            }

            edgesQueue.pop();
        }

        return mstGraph;
    }

    static MatrixGraph *generateMst(const MatrixGraph &graph)
    {
        //auto &vertices = graph.getVertexCount();
        MatrixGraph *mstGraph = new MatrixGraph();
    }
};