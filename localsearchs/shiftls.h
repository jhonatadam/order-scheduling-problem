#ifndef SHIFTLS_H
#define SHIFTLS_H

#include <localsearchs/localsearch.h>

class ShiftLS : public LocalSearch
{
public:
    ShiftLS();

    bool firstImprovement(Solution &sol) override;
    bool bestImprovement(Solution &sol) override;
};

#endif // SHIFTLS_H
