#ifndef HILLCLIMBING_H
#define HILLCLIMBING_H

#include <optimizationmethod.h>
#include <swapls.h>

class HillClimbing : public OptimizationMethod
{
    // local search
    LocalSearch *ls = nullptr;

public:
    HillClimbing(const Instance &inst);
    HillClimbing(const Solution &solution);
    ~HillClimbing() override;

    void _run() override;
};

#endif // HILLCLIMBING_H
