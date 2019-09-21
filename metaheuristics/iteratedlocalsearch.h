#ifndef ITERATEDLOCALSEARCH_H
#define ITERATEDLOCALSEARCH_H

#include <metaheuristics/hillclimbing.h>

class IteratedLocalSearch : public OptimizationMethod
{

    unsigned numberOfIterations = 0;
    // number of swaps in each perturbation
    unsigned swapsPerPerturb = 0;

public:
    IteratedLocalSearch(const Instance &inst,
                        unsigned numberOfIterations,
                        unsigned swapsPerPerturb);


    void _run() override;

};

#endif // ITERATEDLOCALSEARCH_H
