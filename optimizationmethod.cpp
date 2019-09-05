#include "optimizationmethod.h"


OptimizationMethod::OptimizationMethod(const Instance &inst) :
    solution(inst)
{
    
}

void OptimizationMethod::run()
{
    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    _run();

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    elapsedTime = chrono::duration_cast<chrono::duration<double>>(end - start);
}

OptimizationMethod::~OptimizationMethod()
{

}

Solution OptimizationMethod::getSolution() const
{
    return solution;
}

double OptimizationMethod::getSolutionValue() const
{
    return solution.objectiveFunc();
}

double OptimizationMethod::getElapsedTime() const
{
    return elapsedTime.count();
}
