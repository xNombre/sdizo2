#pragma once

#include <chrono> 

typedef unsigned long long timedata;

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

public:
    static void run()
    {

    }
};