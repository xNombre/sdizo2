#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "TimeBench.hpp"
#include "RandomGraphGen.hpp"
#include "Kruskal.hpp"
#include "Prima.hpp"
#include "Dijkstra.hpp"
#include "BellmanFord.hpp"

using namespace std;

void readFromFile(ListGraph &listg, MatrixGraph &matrixg)
{
    string fileName;

    cout << "Enter file name\n";
    cin >> fileName;

    ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("File doesnt exist");

    size_t edges, vertices;
    file >> edges >> vertices;

    for (; edges > 0; edges--) {
        size_t from, to;
        long long weight;
        file >> from >> to >> weight;

        listg.addEdge(from, to, weight);
        matrixg.addEdge(from, to, weight);
    }
}

long long getDataFromUser()
{
    long long val;
    //cout << "Podaj wartosc:\n";
    cin >> val;

    // Clear any garbage
    cin.clear();
    cin.ignore(10000, '\n');

    return val;
}

char getOptionFromUser()
{
    char input;
    std::cin >> input;

    // Clear any garbage
    cin.clear();
    cin.ignore(10000, '\n');

    return input;
}

void mstMenu()
{
    char input;
    ListGraph listGraph(false);
    MatrixGraph matrixGraph(false);

repeat:
    cout << "r - odczyt z pliku\n"
        << "x - losowy graf\n"
        << "k - Kruskal\n"
        << "p - Prima\n"
        << "l - wypisz graf\n"
        << "q - wyjscie\n";
    input = getOptionFromUser();

    switch (input) {
    case 'q':
        return;
        break;
    case 'r':
        listGraph.clear();
        matrixGraph.clear();
        readFromFile(listGraph, matrixGraph);
        break;
    case 'x': {
        listGraph.clear();
        matrixGraph.clear();
        cout << "Count: \n";
        auto count = getDataFromUser();
        cout << "Fill %: \n";
        auto fill = getDataFromUser();
        RandomGraphGen::random(listGraph, matrixGraph, count, fill, false);
        break;
    }
    case 'k': {
        auto resultL = Kruskal::generateMst(listGraph);
        resultL.print();
        auto resultM = Kruskal::generateMst(matrixGraph);
        resultM.print();
        break;
    }
    case 'p': {
        auto resultL = Prima::generateMst(listGraph);
        resultL.print();
        auto resultM = Prima::generateMst(matrixGraph);
        resultM.print();
        break;
    }
    case 'l':
        matrixGraph.print();
        listGraph.print();
        std::cin.get();
        break;
    }

    goto repeat;
}

void shortestPathMenu()
{
    ListGraph listGraph;
    MatrixGraph matrixGraph;
    char input;

repeat:
    cout << "r - odczyt z pliku\n"
        << "x - losowy graf\n"
        << "d - Dijkstra\n"
        << "b - Bellman-Ford\n"
        << "l - wypisz graf\n"
        << "q - wyjscie\n";
    input = getOptionFromUser();

    switch (input) {
    case 'q':
        return;
        break;
    case 'r':
        listGraph.clear();
        matrixGraph.clear();
        readFromFile(listGraph, matrixGraph);
        break;
    case 'x': {
        listGraph.clear();
        matrixGraph.clear();
        cout << "Count: \n";
        auto count = getDataFromUser();
        cout << "Fill %: \n";
        auto fill = getDataFromUser();
        RandomGraphGen::random(listGraph, matrixGraph, count, fill);
        break;
    }
    case 'b': {
        cout << "From: \n";
        auto from = getDataFromUser();
        cout << "To: \n";
        auto to = getDataFromUser();

        auto resultL = BellmanFord::getShortestPathFromTo(listGraph, from, to);
        auto resultM = BellmanFord::getShortestPathFromTo(matrixGraph, from, to);

        resultL.print();
        resultM.print();

        break;
    }
    case 'd': {
        cout << "From: \n";
        auto from = getDataFromUser();
        cout << "To: \n";
        auto to = getDataFromUser();

        auto resultL = Dijkstra::getShortestPathFromTo(listGraph, from, to);
        auto resultM = Dijkstra::getShortestPathFromTo(matrixGraph, from, to);

        resultL.print();
        resultM.print();

        break;
    }
    case 'l':
        matrixGraph.print();
        listGraph.print();
        std::cin.get();
        break;
    }

    goto repeat;
}

int menu()
{
    char input;
    cout << "SDiZO Projekt 2.\n"
        << "b - test automatyczny\n"
        << "m - test manualny\n";
    input = getOptionFromUser();

    if (input == 'b') {
        TimeBenchmark bench;
        bench.run();
        return 0;
    }

    cout << "Wybierz problem:\n"
        << "m - MST\n"
        << "l - Shortest path\n";
    input = getOptionFromUser();

    switch (input) {
    case 'm':
        mstMenu();
        break;
    case 'l':
        shortestPathMenu();
        break;
    }

    return 0;
}