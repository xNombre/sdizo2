#pragma once

#include "Array.hpp"

using std::size_t;

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

        Edge() { };

        size_t from, to;
        size_t weight;

        bool operator< (const Edge &b) const
        {
            return weight < b.weight;
        }

        bool operator> (const Edge &b) const
        {
            return weight > b.weight;
        }

        bool operator== (const Edge &b) const
        {
            return weight == b.weight;
        }
    };

    void addEdge(const size_t &fromVertex, const size_t &toVertex, const size_t &weight)
    {
        edges.push_back(Edge(fromVertex, toVertex, weight));
        
        if (fromVertex > vertexCount)
            vertexCount = fromVertex;
        else if (toVertex > vertexCount)
            vertexCount = toVertex;
    }

    const Array<Edge> &getEdges() const
    {
        return edges;
    }

private:
    Array<Edge> edges;
    size_t vertexCount = 0;
};