#include <iteratedlocalsearch.h>
#include <randommultistart.h>
#include <variableneighborhoodsearch.h>
#include <minduedateheuristic.h>
#include <lateronfirst.h>

int main()
{
    // loading instance
    string instFolder = "../order-scheduling-problem/instances/big/";
    string instName   = "bt_0.8_0.8_0002";
    Instance instance(instFolder + instName);

    vector<tuple<Neighborhood, size_t, size_t>> nbhs;
    nbhs.push_back(make_tuple(Swap, 10, 10));
    nbhs.push_back(make_tuple(Shift, 10, 10));
    nbhs.push_back(make_tuple(Swap, 25, 5));
    nbhs.push_back(make_tuple(Shift, 25, 5));

    // initializing optimization method
    OptimizationMethod *om = new VariableNeighborhoodSearch(instance, 30, nbhs);

    // running optimization method
    om->run();

    // showing resoults
    cout << "Solution value: " << om->getSolutionValue() << endl;
    cout << "Elapsed time:   " << om->getElapsedTime() << " seconds" << endl;

    // cleaning memory
    delete om;

    return 0;
}
