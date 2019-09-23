#ifndef HILLCLIMBING_H
#define HILLCLIMBING_H

#include <optimizationmethod.h>
#include <localsearchs/swapls.h>
#include <localsearchs/shiftls.h>

class HillClimbing : public OptimizationMethod
{
    // local search
    LocalSearch *ls = nullptr;

public:
    HillClimbing(const Instance *inst = nullptr, Neighborhood nbh = Swap);
    HillClimbing(Solution &solution, Neighborhood nbh = Swap);
    ~HillClimbing() override;

    void _run() override;

    void setNeighborhood(Neighborhood nbh);
};

#endif // HILLCLIMBING_H
