#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Instance
{
    // number of machines
    size_t numberOfMachines;
    // number of orders
    size_t numberOfOrders;
    // number of items of each (order, machine) pair
    vector<vector<unsigned>> orderMachine;
    // due dates of orders
    vector<unsigned> dueDates;

    Instance(const string &fileName);

    string toString() const;
};

#endif // INPUT_H
