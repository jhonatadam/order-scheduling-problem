#ifndef VARIABLENEIGHBORHOODDESCENDANT_H
#define VARIABLENEIGHBORHOODDESCENDANT_H

#include <optimizationmethod.h>
#include <localsearchs/swapls.h>
#include <localsearchs/shiftls.h>

class VariableNeighborhoodDescendant : public OptimizationMethod
{
    vector<LocalSearch*> lss;

public:
    VariableNeighborhoodDescendant(const Instance &inst);
    ~VariableNeighborhoodDescendant() override;

    void _run() override;
};

#endif // VARIABLENEIGHBORHOODDESCENDANT_H