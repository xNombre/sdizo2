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

    const vector<size_t> graphSizes = { 20 };//{ 20, 50, 100, 250, 500 };
    const vector<size_t> fillFactors = { 50 };//{ 25, 50, 75, 99 };

    const size_t averagingLoopsCount = 1;
    const size_t datasetGenerationCount = 1;//100;

    template <typename Container, typename Algorithm>
    timedata benchmarkSuiteMST(const size_t &size, const size_t &fill)
    {
        AveragedTimeMeasure containerTimeAveraging;

        for (std::size_t j = 0; j < datasetGenerationCount; j++) {
            Container graph(false);
            RandomGraphGen::random(graph, size, fill, false);

            for (std::size_t i = 0; i < averagingLoopsCount; i++) {
                containerTimeAveraging.benchmarkStart();
                Algorithm::generateMst(graph);
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
            Container graph(false);
            RandomGraphGen::random(graph, size, fill, false);

            for (std::size_t i = 0; i < averagingLoopsCount; i++) {
                containerTimeAveraging.benchmarkStart();
                auto res = Algorithm::getShortestPath(graph, 0);
                for (size_t jj = 0; jj < res.size(); jj++) {
                    cout << jj << ": " << res[jj].weight << " " << res[jj].prev << endl;
                }
                containerTimeAveraging.benchmarkStop();
            }
        }
        return containerTimeAveraging.getAvgElapsedNsec();
    }

public:
    void run()
    {
        for (const auto &size : graphSizes) {
            cout << "Testing graph at size: " << size << "\n//////////////\n";
            for (const auto &fill : fillFactors) {
                cout << "Fill factor: " << fill << "%\n";

                cout << "ListGraph Kruskal:     " <<
                    benchmarkSuiteMST<ListGraph, Kruskal>(size, fill) << "ns\n";
                cout << "ListGraph Prima:       " <<
                    benchmarkSuiteMST<ListGraph, Prima>(size, fill) << "ns\n";
                cout << "ListGraph Dijkstra:    " <<
                    benchmarkSuiteShortest<ListGraph, Dijkstra>(size, fill) << "ns\n";
                cout << "ListGraph BellmanFord: " <<
                    benchmarkSuiteShortest<ListGraph, BellmanFord>(size, fill) << "ns\n";

                cout << endl;
                
                cout << "MatrixGraph Kruskal:     " <<
                    benchmarkSuiteMST<MatrixGraph, Kruskal>(size, fill) << "ns\n";
                cout << "MatrixGraph Prima:       " <<
                    benchmarkSuiteMST<MatrixGraph, Prima>(size, fill) << "ns\n";
                cout << "MatrixGraph Dijkstra:    " <<
                    benchmarkSuiteShortest<MatrixGraph, Dijkstra>(size, fill) << "ns\n";
                cout << "MatrixGraph BellmanFord: " <<
                    benchmarkSuiteShortest<MatrixGraph, BellmanFord>(size, fill) << "ns\n";

                cout << endl;
            }
        }
    }
};