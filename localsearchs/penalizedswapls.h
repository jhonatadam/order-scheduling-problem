#ifndef PENALIZEDSWAPLS_H
#define PENALIZEDSWAPLS_H

#include <localsearchs/localsearch.h>

class PenalizedSwapLS : public LocalSearch
{
    vector<vector<unsigned>> penalities;

public:
    PenalizedSwapLS();

    bool firstImprovement(Solution &sol) override;
    bool bestImprovement(Solution &sol) override;

};

#endif // PENALIZEDSWAPLS_H
