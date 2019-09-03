#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>

using namespace std;

struct Instance
{
    size_t numberOfMachines;
    size_t numberOfOrders;

    Instance(string fileName);

    string toString();
};

#endif // INPUT_H
