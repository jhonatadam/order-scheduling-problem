#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H


class LocalSearch
{
public:
    LocalSearch();
    virtual ~LocalSearch() = 0;

    virtual void firstImprovement() = 0;
    virtual void bestImprovement() = 0;
};

#endif // LOCALSEARCH_H
