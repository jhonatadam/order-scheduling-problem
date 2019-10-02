#ifndef ITERATEDLOCALSEARCH_H
#define ITERATEDLOCALSEARCH_H

#include <metaheuristics/hillclimbing.h>
#include <metaheuristics/variableneighborhooddescendant.h>

class IteratedLocalSearch : public OptimizationMethod
{

    unsigned numberOfIterations = 0;
    // number of swaps in each perturbation
    unsigned swapsPerPerturb = 0;

public:
    IteratedLocalSearch(unsigned numberOfIterations,
                        unsigned swapsPerPerturb,
                        const Instance *inst = nullptr);


    void _run() override;

};

#endif // ITERATEDLOCALSEARCH_H
