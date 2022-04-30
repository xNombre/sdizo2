#pragma once

#include <chrono> 
#include <vector>

#include "RandomGraphGen.hpp"
#include "Kruskal.hpp"
#include "Prima.hpp"
#include "Dijkstra.hpp"
#include "BellmanFord.hpp"

typedef unsigned long long timedata;

using namespace std;
class TimeBenchmark {
    class AveragedTimeMeasure {
        std::chrono::high_resolution_clock::time_point start, end;
        std::chrono::duration<double> elapsed = std::chrono::duration<double>::zero();
        std::size_t times = 0;

    public:
        void benchmarkStart()
        {
            start = std::chrono::high_resolution_clock::now();
        }

        void benchmarkStop()
        {
            end = std::chrono::high_resolution_clock::now();

            elapsed += end - start;
            times++;
        }

        timedata getAvgElapsedNsec()
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() / times;
        }
    };

    const vector<size_t> graphSizes = { 50, 70, 100, 120, 150 };
    const vector<size_t> fillFactors = { 25, 50, 75, 99 };

    const size_t averagingLoopsCount = 1;
    const size_t datasetGenerationCount = 15;

    template <typename Container, typename Algorithm>
    timedata benchmarkSuiteMST(const size_t &size, const size_t &fill)
    {
        AveragedTimeMeasure containerTimeAveraging;

        for (std::size_t j = 0; j < datasetGenerationCount; j++) {
            Container graph(false);
            RandomGraphGen::random(graph, size, fill, false);

            for (std::size_t i = 0; i < averagingLoopsCount; i++) {
                containerTimeAveraging.benchmarkStart();
                volatile auto tmp = Algorithm::generateMst(graph);
                containerTimeAveraging.benchmarkStop();
            }
        }
        return containerTimeAveraging.getAvgElapsedNsec();
    }

    template <typename Container, typename Algorithm>
    timedata benchmarkSuiteShortest(const size_t &size, const size_t &fill)
    {
        AveragedTimeMeasure containerTimeAveraging;

        for (std::size_t j = 0; j < datasetGenerationCount; j++) {
            Container graph;
            RandomGraphGen::random(graph, size, fill);

            for (std::size_t i = 0; i < averagingLoopsCount; i++) {
                containerTimeAveraging.benchmarkStart();
                volatile auto tmp = Algorithm::getShortestPath(graph);
                containerTimeAveraging.benchmarkStop();
            }
        }
        return containerTimeAveraging.getAvgElapsedNsec();
    }

public:
    void run()
    {
        cout << "Graphs sizes: ";
        for (const auto &size : graphSizes) {
            cout << size << " ";
        }
        cout << "Graphs fill factors: ";
        for (const auto &fill : fillFactors) {
            cout << fill << " ";
        }

        cout << "\nListGraph Kruskal\n";
        for (const auto &fill : fillFactors) {
            for (const auto &size : graphSizes) {
                cout << size << " " <<
                    benchmarkSuiteMST<ListGraph, Kruskal>(size, fill) << "\n";
            }
            cout << endl;
        }

        cout << "ListGraph Prima\n";
        for (const auto &fill : fillFactors) {
            for (const auto &size : graphSizes) {
                cout << size << " " <<
                    benchmarkSuiteMST<ListGraph, Prima>(size, fill) << "\n";
            }
            cout << endl;
        }

        cout << "ListGraph Dijkstra\n";
        for (const auto &fill : fillFactors) {
            for (const auto &size : graphSizes) {
                cout << size << " " <<
                    benchmarkSuiteShortest<ListGraph, Dijkstra>(size, fill) << "\n";
            }
            cout << endl;
        }

        cout << "ListGraph BellmanFord\n";
        for (const auto &fill : fillFactors) {
            for (const auto &size : graphSizes) {
                cout << size << " " <<
                    benchmarkSuiteShortest<ListGraph, BellmanFord>(size, fill) << "\n";
            }
            cout << endl;
        }

        cout << "MatrixGraph Kruskal\n";
        for (const auto &fill : fillFactors) {
            for (const auto &size : graphSizes) {
                cout << size << " " <<
                    benchmarkSuiteMST<MatrixGraph, Kruskal>(size, fill) << "\n";
            }
            cout << endl;
        }

        cout << "MatrixGraph Prima\n";
        for (const auto &fill : fillFactors) {
            for (const auto &size : graphSizes) {
                cout << size << " " <<
                    benchmarkSuiteMST<MatrixGraph, Prima>(size, fill) << "\n";
            }
            cout << endl;
        }

        cout << "MatrixGraph Dijkstra\n";
        for (const auto &fill : fillFactors) {
            for (const auto &size : graphSizes) {
                cout << size << " " <<
                    benchmarkSuiteShortest<MatrixGraph, Dijkstra>(size, fill) << "\n";
            }
            cout << endl;
        }

        cout << "MatrixGraph BellmanFord\n";
        for (const auto &fill : fillFactors) {
            for (const auto &size : graphSizes) {
                cout << size << " " <<
                    benchmarkSuiteShortest<MatrixGraph, BellmanFord>(size, fill) << "\n";
            }
            cout << endl;
        }
    }
};