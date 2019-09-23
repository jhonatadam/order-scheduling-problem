#ifndef MINDUEDATEHEURISTIC_H
#define MINDUEDATEHEURISTIC_H

#include <optimizationmethod.h>

class MinDueDateHeuristic : public OptimizationMethod
{
public:
    MinDueDateHeuristic(const Instance *inst = nullptr);

    void _run() override;
};

#endif // MINDUEDATEHEURISTIC_H
