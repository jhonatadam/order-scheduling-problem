#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include <solution.h>

enum Neighborhood {Swap, Shift};

class LocalSearch
{
public:
    LocalSearch();
    virtual ~LocalSearch() = 0;

    virtual bool firstImprovement(Solution &sol) = 0;
    virtual bool bestImprovement(Solution &sol) = 0;
};

#endif // LOCALSEARCH_H
