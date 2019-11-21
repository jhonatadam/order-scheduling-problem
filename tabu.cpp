#include "tabu.h"

Tabu::Tabu(const unsigned tenure) :
    tenure(tenure)
{

}

bool Tabu::contains(Solution &sol)
{
    if (tabu.empty())
        return false;

//    return tt.contains(sol, &tt.root);

    vector<unsigned> tardAcc(sol.getNumOfSlots());
    for (unsigned slot = 0; slot < sol.getNumOfSlots(); slot++) {
        tardAcc[slot] = sol.getTardAcc(slot);
    }

    for (unsigned *e : tabu) {
        if (equal(tardAcc.begin(), tardAcc.end(), e)) {
            return true;
        }
    }

    return false;
}

void Tabu::insert(Solution &sol)
{
//    if (tt.contains(sol, &tt.root))
//        return;

//    tt.insert(sol, &tt.root);

    unsigned* newElement = nullptr;
    if (tabu.size() < tenure) {
        newElement = new unsigned[sol.getNumOfSlots()];
    } else {
        newElement = tabu.front();
        tabu.pop_front();
    }

    for (unsigned slot = 0; slot < sol.getNumOfSlots(); slot++) {
        newElement[slot] = sol.getTardAcc(slot);
    }

    tabu.push_back(newElement);
}

void Tabu::clean()
{
    while(!tabu.empty()) {
        delete [] tabu.front();
        tabu.pop_front();
    }
}
