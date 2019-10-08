#ifndef GUIDEDLOCALSEARCH_H
#define GUIDEDLOCALSEARCH_H

#include <metaheuristics/penalizedvnd.h>

class GuidedLocalSearch : public OptimizationMethod
{
    // number of iterations
    size_t numIt;
    // penalities
    vector<vector<unsigned>> penalities;

    void initilizePenalities();
    void penalize(Solution &so);

public:
    GuidedLocalSearch(const size_t numIt, const Instance *inst);

    void _run() override;
};

#endif // GUIDEDLOCALSEARCH_H
