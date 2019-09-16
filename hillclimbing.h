#ifndef HILLCLIMBING_H
#define HILLCLIMBING_H

#include <optimizationmethod.h>
#include <swapls.h>
#include <shiftls.h>

class HillClimbing : public OptimizationMethod
{
    // local search
    LocalSearch *ls = nullptr;

public:
    HillClimbing(const Instance &inst, Neighborhood nbh = Swap);
    HillClimbing(const Solution &solution, Neighborhood nbh = Swap);
    ~HillClimbing() override;

    void _run() override;

    void setNeighborhood(Neighborhood nbh);
};

#endif // HILLCLIMBING_H
