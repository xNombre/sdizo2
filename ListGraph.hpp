#pragma once

#include <iostream>

#include "Array.hpp"
#include "Edge.hpp"

using std::size_t;

#define RST  "\x1B[0m"
#define KRED  "\x1B[41m"
#define KBLU  "\x1B[44m"

class ListGraph {
public:
    struct AdjacentEdge {
        size_t edge;
        size_t weight;

        AdjacentEdge(size_t edge, size_t weight) : edge(edge), weight(weight) { }
        AdjacentEdge() { }
    };

    ListGraph(bool isDirected = true) : isDirected(isDirected) { }

    const size_t &getEdgesCount() const
    {
        return edgesCount;
    }

    const size_t &getVertexCount() const
    {
        return edges.size();
    }

    void addEdge(const size_t &fromVertex, const size_t &toVertex, const size_t &weight)
    {
        auto max = std::max(fromVertex, toVertex) + 1;
        if (max > edges.size())
            edges.resize(max);

        edges[fromVertex].push_back(AdjacentEdge(toVertex, weight));
        
        if (!isDirected && fromVertex != toVertex)
            edges[toVertex].push_back(AdjacentEdge(fromVertex, weight));

        edgesCount++;
    }

    const Array<AdjacentEdge> &getVerticesAdjacentTo(const size_t &vertex) const
    {
        return edges[vertex];
    }

    void print() const
    {
        if (edges.size() == 0)
            return;

        for (size_t i = 0; i < edges.size(); i++) {            
            std::cout << KBLU << i << RST << ": ";

            for (size_t j = 0; j < edges[i].size(); j++) {
                std::cout << "[" << edges[i][j].edge << ", " << edges[i][j].weight << "] ";
            }
            
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    void clear()
    {
        edgesCount = 0;
        edges = Array<Array<AdjacentEdge>>();
    }

private:
    Array<Array<AdjacentEdge>> edges;
    size_t edgesCount = 0;
    bool isDirected;
};