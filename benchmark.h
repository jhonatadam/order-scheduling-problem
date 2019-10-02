#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <dirent.h>
#include <sys/types.h>

#include <optimizationmethod.h>

struct Experiment {
    // instance name
    string instName;
    // method name
    string methodName;
    // runtime
    double runtime;
    // solution
    unsigned* scheduling;
    // solution value
    unsigned schedValue;

    Experiment(Instance *inst, OptimizationMethod *optMethod);
    ~Experiment();

    string toString();
};

class Benchmark
{
    // instances
    vector<Instance*>      instances;
    // methods to be performed
    vector<OptimizationMethod*> optMethods;
    // experiments performed
    vector<Experiment*>  experiments;

public:
    Benchmark(const string& instDir, const vector<OptimizationMethod*> &optMethods);
    ~Benchmark();

    void loadInstances(const string& instDir);

    void run();

    void clean();
};

#endif // BENCHMARK_H
