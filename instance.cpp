#include <instance.h>


Instance::Instance(const string &fileName)
{
    ifstream ifs(fileName);
    
    if (!ifs.is_open()) {
        cerr << "Erro: não foi possível abrir o arquivo \"" +
                fileName + "\"" << endl;
        exit(EXIT_FAILURE);
    }

    // reading instance data
    ifs >> numberOfMachines >> numberOfOrders;
    dueDates.resize(numberOfOrders);
    for (unsigned order = 0; order < numberOfOrders; order++) {
        orderMachine.push_back(vector<unsigned>(numberOfMachines));
        for (unsigned machine = 0; machine < numberOfMachines; machine++) {
            ifs >> orderMachine[order][machine];
        }
        ifs >> dueDates[order];
    }

    ifs.close();
}

string Instance::toString() const
{
    string machines = "Number of Machines: " + to_string(numberOfMachines) + "\n";

    string orders   = "Number of Orders:   " + to_string(numberOfOrders) + "\n\n";

    unsigned cellSize = 15;
    string orderMachineTable = "| Orders/Machine |";
    for (unsigned machine = 0; machine < numberOfMachines; machine++) {
        string machStr = to_string(machine);
        orderMachineTable +=  string(cellSize - machStr.length(), ' ') + machStr + " |";
    }
    orderMachineTable += " Due Time       |\n";

    for (unsigned order = 0; order < numberOfOrders; order++) {
        string ordStr = to_string(order);
        orderMachineTable += "|" + string(cellSize - ordStr.length(), ' ') + ordStr + " |";
        for (unsigned machine = 0; machine < numberOfMachines; machine++) {
            string ordMacStr = to_string(orderMachine[order][machine]);
            orderMachineTable += string(cellSize - ordMacStr.length(), ' ') + ordMacStr + " |";
        }
        string dueDateStr = to_string(dueDates[order]);
        orderMachineTable += string(cellSize - dueDateStr.length(), ' ') + dueDateStr + " |\n";
    }

    return machines + orders + orderMachineTable;
}
