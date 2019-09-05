#ifndef OPTIMIZATIONMETHOD_H
#define OPTIMIZATIONMETHOD_H

#include <chrono>

#include <solution.h>

class OptimizationMethod
{
protected:
    // solution
    Solution solution;
    // enlapsed time in seconds
    chrono::duration<double> elapsedTime;

public:
    OptimizationMethod(const Instance &Inst);
    virtual ~OptimizationMethod() = 0;

    // executes _run and gets the elapsed time
    void run();
    // implemented by subclasses
    virtual void _run() = 0;

    // getters
    Solution getSolution() const;
    double getSolutionValue() const;
    double getElapsedTime() const;

};

#endif // OPTIMIZATIONMETHOD_H
