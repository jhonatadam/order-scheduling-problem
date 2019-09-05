#include <randommultistart.h>


int main()
{
    string instFolder = "../order-scheduling-problem/instances/big/";
    string instName   = "bt_0.2_0.2_0001";

    Instance instance(instFolder + instName);

    RandomMultiStart rms(instance, 10);

    rms.run();

    cout << "Solution value: " << rms.getSolutionValue() << endl;
    cout << "Elapsed time:   " << rms.getElapsedTime() << " seconds" << endl;
    return 0;
}
