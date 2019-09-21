#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <optimizationmethod.h>

struct Experiment {
    string methodName;
    string instance;
    vector<unsigned> scheduling;
    unsigned schedulingValue;
    double execTime;
};

class Benchmark
{
    // instances
    vector<Instance>      instances;
    // methods to be performed
    vector<OptimizationMethod*> oms;
    // experiments performed
    vector<Experiment>  experiments;

public:
    Benchmark();
};

#endif // BENCHMARK_H
