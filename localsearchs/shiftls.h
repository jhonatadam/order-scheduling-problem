#ifndef SHIFTLS_H
#define SHIFTLS_H

#include <localsearchs/localsearch.h>

class ShiftLS : public LocalSearch
{
public:
    ShiftLS();

    bool firstImprovement(Solution &sol) override;
    bool firstImprovement(Solution &sol, vector<vector<unsigned int> > &penalities) override;
    bool bestImprovement(Solution &sol) override;
    bool bestImprovement(Solution &sol, vector<vector<unsigned int> > &penalities) override;
};

#endif // SHIFTLS_H
