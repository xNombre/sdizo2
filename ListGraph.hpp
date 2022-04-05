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
            vertexCount = fromVertex;
        else if (toVertex > vertexCount)
            vertexCount = toVertex;
    }

    void addEdge(const Edge &edge)
    {
        edges.push_back(Edge(edge));
    }
    
    const Array<Edge> &getEdges() const
    {
        return edges;
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