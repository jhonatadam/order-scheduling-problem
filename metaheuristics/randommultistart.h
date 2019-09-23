#ifndef RANDOMMULTISTART_H
#define RANDOMMULTISTART_H

#include <metaheuristics/hillclimbing.h>

class RandomMultiStart : public OptimizationMethod
{
    unsigned numberOfIterations;
public:
    RandomMultiStart(const unsigned numberOfIterations,
                     const Instance *inst = nullptr);

    void _run() override;
};

#endif // RANDOMMULTISTART_H
