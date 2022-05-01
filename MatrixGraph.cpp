#include "MatrixGraph.hpp"




void MatrixGraph::addEdge(const size_t &from, const size_t &to, const long long &weight)
{
    // Add new vertices if necessary
    const auto &newSize = std::max(from, to) + 1;
    const auto oldSize = matrix.size();
    if (newSize > oldSize) {
        matrix.resize(newSize);

        const auto &edgesCount = matrix[0].size();
        for (size_t i = oldSize; i < newSize; i++) {
            matrix[i].resize(edgesCount);
        }
    }

    // Add new edge
    for (size_t i = 0; i < matrix.size(); i++) {
        if (i == from)
            // When edge is a cycle over same vertex make its weight positive
            matrix[i].push_back(isDirected && from != to ? -weight : weight);
        else if (i == to)
            matrix[i].push_back(weight);
        else
            matrix[i].push_back(0);
    }
}

const IncidenceMatrix &MatrixGraph::getMatrix() const
{
    return matrix;
}

const size_t &MatrixGraph::getVertexCount() const
{
    return matrix.size();
}

const size_t MatrixGraph::getEdgesCount() const
{
    if (matrix.size() != 0)
        return matrix[0].size();
    else
        return 0;
}

void MatrixGraph::print() const
{
    const auto &count = getEdgesCount();
    const auto &vertices = getVertexCount();

    if (vertices == 0) {
        std::cout << KRED << "Graf jest pusty!" << RST << std::endl;
        return;
    }

    std::cout << "   " << KRED;
    for (size_t j = 0; j < count; j++) {
        std::cout << j << "  ";

        if (j < 10)
            std::cout << " ";
    }
    std::cout << RST << std::endl;

    for (size_t i = 0; i < vertices; i++) {
        std::cout << KBLU << i << RST << " ";
        if (i < 10)
            std::cout << " ";

        for (size_t j = 0; j < count; j++) {
            std::cout << matrix[i][j] << " ";

            if (matrix[i][j] < 10 && matrix[i][j] > -1)
                std::cout << "  ";
            else if (matrix[i][j] > -10)
                std::cout << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void MatrixGraph::clear()
{
    matrix = IncidenceMatrix();
}
