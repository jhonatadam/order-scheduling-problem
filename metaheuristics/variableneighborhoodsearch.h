#ifndef VARIABLENEIGHBORHOODSEARCH_H
#define VARIABLENEIGHBORHOODSEARCH_H

#include <tuple>

#include <optimizationmethod.h>
#include <metaheuristics/variableneighborhooddescendant.h>

class VariableNeighborhoodSearch : public OptimizationMethod
{
    // neighborhoods
    vector<tuple<Neighborhood, size_t, size_t> > nbhs;
    // maximum number of iterations
    unsigned maxIt = 0;

public:
    VariableNeighborhoodSearch(
            const Instance &inst, const unsigned maxIt,
            vector<tuple<Neighborhood, size_t, size_t>> &nbhs);

    ~VariableNeighborhoodSearch() override;

    void _run() override;
};

#endif // VARIABLENEIGHBORHOODSEARCH_H
