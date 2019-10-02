#include "optimizationmethod.h"


string OptimizationMethod::getName() const
{
    return name;
}

OptimizationMethod::OptimizationMethod(const Instance *inst) :
    solution(inst)
{
    
}

OptimizationMethod::OptimizationMethod(Solution &solution) :
    solution(solution.getInstance())
{
    this->solution.copy(solution);
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

Solution &OptimizationMethod::getSolution()
{
    return solution;
}

unsigned OptimizationMethod::getSolutionValue()
{
    return solution.getValue();
}

double OptimizationMethod::getElapsedTime() const
{
    return elapsedTime.count();
}

void OptimizationMethod::setSolution(const Solution &other)
{
    this->solution.copy(other);
}

void OptimizationMethod::setInstance(const Instance *inst)
{
    this->solution.setInstance(inst);
}
