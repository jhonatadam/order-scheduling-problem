#ifndef OPTIMIZATIONMETHOD_H
#define OPTIMIZATIONMETHOD_H

#include <solution.h>

class OptimizationMethod
{
protected:
    // method name
    string name;
    // solution
    Solution solution;
    // enlapsed time in seconds
    chrono::duration<double> elapsedTime = chrono::duration<double>::zero();

public:
    OptimizationMethod(const Instance *Inst);
    OptimizationMethod(Solution &solution);
    virtual ~OptimizationMethod() = 0;

    // executes _run and gets the elapsed time
    void run();
    // implemented by subclasses
    virtual void _run() = 0;

    // getters
    Solution &getSolution();
    unsigned getSolutionValue();
    double getElapsedTime() const;
    string getName() const;

    // setters
    void setSolution(const Solution &other);
    void setInstance(const Instance *inst);
};

#endif // OPTIMIZATIONMETHOD_H
