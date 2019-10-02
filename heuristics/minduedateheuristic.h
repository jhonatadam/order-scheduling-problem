#ifndef MINDUEDATEHEURISTIC_H
#define MINDUEDATEHEURISTIC_H

#include <optimizationmethod.h>

class MinDueDateHeuristic : public OptimizationMethod
{
    vector<unsigned> tempSched;
    // number of candidates in the random choose
    unsigned numOfCand;

public:
    MinDueDateHeuristic(const unsigned numOfCand = 1, const Instance *inst = nullptr);

    void _run() override;
};

#endif // MINDUEDATEHEURISTIC_H
