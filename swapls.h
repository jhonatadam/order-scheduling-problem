#ifndef SWAPLS_H
#define SWAPLS_H

#include <localsearch.h>

class SwapLS : public LocalSearch
{
public:
    SwapLS();
    ~SwapLS() override;

    bool firstImprovement(Solution &sol) override;
    bool bestImprovement(Solution &sol) override;
};

#endif // SWAPLS_H
