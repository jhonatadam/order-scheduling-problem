#ifndef VARIABLENEIGHBORHOODDESCENDANT_H
#define VARIABLENEIGHBORHOODDESCENDANT_H

#include <optimizationmethod.h>
#include <swapls.h>
#include <shiftls.h>

class VariableNeighborhoodDescendant : public OptimizationMethod
{
    vector<LocalSearch*> lss;

public:
    VariableNeighborhoodDescendant(const Instance &inst);
    ~VariableNeighborhoodDescendant() override;

    void _run() override;
};

#endif // VARIABLENEIGHBORHOODDESCENDANT_H
