#pragma once

#include "UnionFind.hpp"
#include "MinHeap.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"

using std::size_t;

class Kruskal {

public:

    static ListGraph generateMst(const ListGraph &graph)
    {
        //const auto &edges = graph.getEdges();
        const auto &vertices = graph.getVertexCount();

        ListGraph mstGraph(false);

        if (vertices == 0)
            return mstGraph;
        
        UnionFind forest(vertices);
        MinHeap<Edge> edgesQueue;

        // Push all edges to the heap
        for (size_t vertex = 0; vertex < vertices; vertex++) {
            auto adjacent = graph.getVerticesAdjacentTo(vertex);
            for (size_t adj = 0; adj < adjacent.size(); adj++) {
                edgesQueue.push(Edge(vertex, adjacent[adj].edge, adjacent[adj].weight));
            }

        }

        // MST will always have (vertices - 1) edges
        for (size_t addedEdges = 0; addedEdges < vertices - 1 && !edgesQueue.empty(); ) {
            const auto &node = edgesQueue.top();

            const auto &aParent = forest.findNode(node.from);
            const auto &bParent = forest.findNode(node.to);

            if (aParent != bParent) {
                // Vertices not connected, union em
                forest.unionNodes(node.from, node.to);
                // Add edge to mst
                mstGraph.addEdge(node.from, node.to, node.weight);

                addedEdges++;
            }

            edgesQueue.pop();
        }

        return mstGraph;
    }

    static MatrixGraph generateMst(const MatrixGraph &graph)
    {
        const auto &vertices = graph.getVertexCount();
        const auto &edges = graph.getEdgesCount();
        const auto &matrix = graph.getMatrix();

        MatrixGraph mstGraph(false);
        
        if (vertices == 0)
            return mstGraph;
        
        MinHeap<Edge> edgesQueue;
        UnionFind forest(vertices);
        
        // Push all edges to the heap
        for (size_t vertex = 0; vertex < vertices; vertex++) {
            for (size_t edge = 0; edge < edges; edge++) {
                if (matrix[vertex][edge] > 0) {
                    edgesQueue.push(
                        Edge(vertex, graph.findOtherVertexOfEdge(edge, vertex),
                             matrix[vertex][edge])
                    );
                }
            }
        }

        // MST will always have (vertices - 1) edges
        for (size_t addedEdges = 0; addedEdges < vertices - 1 && !edgesQueue.empty(); ) {
            const auto &node = edgesQueue.top();

            const auto &aParent = forest.findNode(node.from);
            const auto &bParent = forest.findNode(node.to);

            if (aParent != bParent) {
                // Vertices not connected, union em
                forest.unionNodes(node.from, node.to);
                // Add edge to mst
                mstGraph.addEdge(node.from, node.to, node.weight);

                addedEdges++;
            }

            edgesQueue.pop();
        }

        return mstGraph;
    }

};