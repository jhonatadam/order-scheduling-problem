#ifndef RANDOMMULTISTART_H
#define RANDOMMULTISTART_H

#include <hillclimbing.h>

class RandomMultiStart : public OptimizationMethod
{
    unsigned numberOfIterations;
public:
    RandomMultiStart(const Instance &inst, const unsigned numberOfIterations);

    void _run() override;
};

#endif // RANDOMMULTISTART_H
