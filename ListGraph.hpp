#pragma once

#include "Array.hpp"
#include <iostream>

using std::size_t;

#define RST  "\x1B[0m"
#define KRED  "\x1B[41m"
#define KBLU  "\x1B[44m"

class ListGraph {
public:
    const size_t &getVertexCount() const
    {
        return vertexCount;
    }

    void setVertexCount(const size_t &count)
    {
        vertexCount = count;
    }

    struct Edge {
        Edge(const size_t &fromVertex, const size_t &toVertex, const size_t &weight) : from(fromVertex), to(toVertex), weight(weight) { };

        Edge(const Edge &edge) : from(edge.from), to(edge.to), weight(edge.weight) { };

        Edge() { };

        size_t from, to;
        size_t weight;

        friend bool operator< (const Edge &a, const Edge &b);
        friend bool operator> (const Edge &a, const Edge &b);
        friend bool operator== (const Edge &a, const Edge &b);
    };

    void addEdge(const size_t &fromVertex, const size_t &toVertex, const size_t &weight)
    {
        edges.push_back(Edge(fromVertex, toVertex, weight));

        if (fromVertex > vertexCount)
            vertexCount = fromVertex + 1;
        else if (toVertex > vertexCount)
            vertexCount = toVertex + 1;
    }

    void addEdge(const Edge &edge)
    {
        edges.push_back(Edge(edge));
    }

    const Array<Edge> &getEdges() const
    {
        return edges;
    }

    void print() const
    {
        std::cout << KRED << "F  T  W " << RST << std::endl;
        
        for (size_t i = 0; i < edges.size(); i++) {
            std::cout << edges[i].from << " ";

            if (edges[i].from < 10)
                std::cout << " ";

            std::cout << edges[i].to << " ";

            if (edges[i].to < 10)
                std::cout << " ";

            std::cout << edges[i].weight;
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

private:
    Array<Edge> edges;
    size_t vertexCount = 0;
};

bool operator< (const ListGraph::Edge &a, const ListGraph::Edge &b)
{
    return a.weight < b.weight;
}

bool operator> (const ListGraph::Edge &a, const ListGraph::Edge &b)
{
    return a.weight > b.weight;
}

bool operator== (const ListGraph::Edge &a, const ListGraph::Edge &b)
{
    return a.weight == b.weight;
}