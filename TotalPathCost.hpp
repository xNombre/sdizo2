#pragma once

#include <iostream>

#include "Array.hpp"

#define RST  "\x1B[0m"
#define KRED  "\x1B[41m"
#define KBLU  "\x1B[44m"

struct TotalPathCost {
    size_t totalCost = SIZE_MAX;
    Array<size_t> path;

    void print() const
    {
        if (totalCost == SIZE_MAX) {
            std::cout << KRED << "Nie ma drogi!" << RST << std::endl;
            return;
        }

        for (size_t i = 0; i < path.size() - 1; i++) {
            std::cout << KBLU << path[i] << RST << " -> ";
        }

        std::cout << KBLU << path[path.size() - 1] << RST;
        std::cout << "\nTotal cost: " << KRED << totalCost << RST << std::endl;
    }
};