#ifndef GRASP_H
#define GRASP_H

#include <metaheuristics/variableneighborhooddescendant.h>
#include <heuristics/minduedateheuristic.h>
#include <heuristics/lateronfirst.h>

class GRASP : public OptimizationMethod
{
    // number of iterations
    size_t numOfIte;
    // random heuristic
    OptimizationMethod *heuristic;

public:
    GRASP(unsigned numOfIte, unsigned numOfCand, const Instance *inst = nullptr);
    ~GRASP() override;

    void _run() override;
};

#endif // GRASP_H
