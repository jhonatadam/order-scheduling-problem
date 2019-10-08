#ifndef SWAPLS_H
#define SWAPLS_H

#include <localsearchs/localsearch.h>

class SwapLS : public LocalSearch
{
public:
    SwapLS();
    ~SwapLS() override;

    bool firstImprovement(Solution &sol) override;
    bool firstImprovement(Solution &sol, vector<vector<unsigned int> > &penalities) override;
    bool bestImprovement(Solution &sol) override;
    bool bestImprovement(Solution &sol, vector<vector<unsigned int> > &penalities) override;
};

#endif // SWAPLS_H
