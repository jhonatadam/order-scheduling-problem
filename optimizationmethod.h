#ifndef OPTIMIZATIONMETHOD_H
#define OPTIMIZATIONMETHOD_H

#include <solution.h>

class OptimizationMethod
{
protected:
    // solution
    Solution solution;
    // enlapsed time in seconds
    chrono::duration<double> elapsedTime = chrono::duration<double>::zero();

public:
    OptimizationMethod(const Instance &Inst);
    OptimizationMethod(const Solution &solution);
    virtual ~OptimizationMethod() = 0;

    // executes _run and gets the elapsed time
    void run();
    // implemented by subclasses
    virtual void _run() = 0;

    // getters
    Solution &getSolution();
    double getSolutionValue();
    double getElapsedTime() const;

    // setters
    void setSolution(const Solution &other);

};

#endif // OPTIMIZATIONMETHOD_H
