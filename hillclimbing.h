#ifndef HILLCLIMBING_H
#define HILLCLIMBING_H

#include <optimizationmethod.h>
#include <swapls.h>

class HillClimbing : public OptimizationMethod
{
    Solution sol;

    LocalSearch *ls = nullptr;

public:
    HillClimbing(const Instance &inst);
    ~HillClimbing() override;

    bool run() override;
};

#endif // HILLCLIMBING_H
