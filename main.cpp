#include <iteratedlocalsearch.h>
#include <randommultistart.h>

int main()
{
    // loading instance
    string instFolder = "../order-scheduling-problem/instances/big/";
    string instName   = "bt_0.8_0.8_0001";
    Instance instance(instFolder + instName);

    Solution sol(instance);

    // initializing optimization method
    OptimizationMethod *om = new HillClimbing(instance);

    // running optimization method
    om->run();

    // showing resoults
    cout << "Solution value: " << om->getSolutionValue() << endl;
    cout << "Elapsed time:   " << om->getElapsedTime() << " seconds" << endl;

    // cleaning memory
    delete om;

    return 0;
}
