#include <instance.h>



Instance::Instance(std::string fileName) {
    ifstream ifs(fileName);

    if (!ifs.is_open()) {
        cerr << "Erro: não foi possível abrir o arquivo \"" +
                fileName + "\"" << endl;
        exit(EXIT_FAILURE);
    }

    ifs >> numberOfMachines >> numberOfOrders;




    ifs.close();
}

std::string Instance::toString()
{
    string machines = "Number of Machines: " + to_string(numberOfMachines) + "\n";

    string orders   = "Number of Orders:   " + to_string(numberOfOrders) + "\n";

//    str +=

    return machines + orders;
}
