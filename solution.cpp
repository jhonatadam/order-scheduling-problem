#include "solution.h"


Solution::Solution(const Instance *instance)
{
    this->setInstance(instance);
}

const vector<unsigned>& Solution::getScheduling()
{
    return scheduling;
}

bool Solution::operator<(Solution &other)
{
    return this->getValue() < other.getValue();
}

bool Solution::operator==(Solution &other)
{
    if (this->getNumOfSlots() != other.getNumOfSlots())
        return false;

    for (size_t slot = 0; slot < this->getNumOfSlots(); slot++)
        if (this->scheduling[slot] != other.scheduling[slot])
            return false;

    return true;
}

void Solution::_swap(size_t slotA, size_t slotB)
{
    unsigned aux = scheduling[slotA];
    scheduling[slotA] = scheduling[slotB];
    scheduling[slotB] = aux;
}

void Solution::_shift(size_t from, size_t to)
{
    unsigned order = scheduling[from];

    if (from < to) {
        for (size_t slot = from; slot < to; slot++) {
            scheduling[slot] = scheduling[slot + 1];
        }
    } else if (to < from) {
        for (size_t slot = from; slot > to; slot--) {
            scheduling[slot] = scheduling[slot - 1];
        }
    }

    scheduling[to] = order;
}

void Solution::updateValue(size_t begin, size_t end)
{
    if (begin == end)
        return;

    int prevEndAccTardiness = int(tardinessAcc[end]);

    for (size_t slot = begin; slot <= end; slot++) {
        unsigned order = scheduling[slot];
        unsigned maxTime = 0;
        for (size_t machine = 0; machine < instance->numberOfMachines; machine++) {
            timeAcc[slot][machine] = slot > 0 ? timeAcc[slot - 1][machine] : 0;
            timeAcc[slot][machine] += instance->orderMachine[order][machine];

            if (timeAcc[slot][machine] > maxTime)
                maxTime = timeAcc[slot][machine];
        }
        // updating tardiness accumulated
        tardinessAcc[slot] = slot > 0 ? tardinessAcc[slot - 1] : 0;
        tardinessAcc[slot] += maxTime > instance->dueDates[order] ?
                    maxTime - instance->dueDates[order] : 0;
    }

    int endDiff = int(tardinessAcc[end]) - prevEndAccTardiness;
    for (size_t slot = end + 1; slot < scheduling.size(); slot++) {
        tardinessAcc[slot] = unsigned(int(tardinessAcc[slot]) + endDiff);
    }
}

int Solution::valueGain(size_t begin, size_t end)
{
    unsigned tardAcc;
    unsigned maxTardAcc = 0;
    unsigned endTime;
    vector<unsigned> maxEndTime(end - begin + 1, 0);
    for (size_t machine = 0; machine < instance->numberOfMachines; machine++) {
        tardAcc = begin > 0 ? tardinessAcc[begin - 1] : 0;
        endTime = begin > 0 ? timeAcc[begin - 1][machine] : 0;
        for (size_t slot = begin; slot <= end; slot++) {
            endTime += instance->orderMachine[scheduling[slot]][machine];
            size_t maxEndTimeIdx = slot - begin;

            if (endTime > maxEndTime[maxEndTimeIdx])
                maxEndTime[maxEndTimeIdx] = endTime;

            if (maxEndTime[maxEndTimeIdx] > instance->dueDates[scheduling[slot]])
                tardAcc += maxEndTime[maxEndTimeIdx] - instance->dueDates[scheduling[slot]];

            if (tardAcc > tardinessAcc[end])
                return int(tardAcc) - int(tardinessAcc[end]);
        }

        if (tardAcc > maxTardAcc) {
            maxTardAcc = tardAcc;
        }
    }

    return int(maxTardAcc) - int(tardinessAcc[end]);
}

void Solution::swap(size_t slotA, size_t slotB)
{
    if (slotA == slotB)
        return;
    this->_swap(slotA, slotB);

    updateValue(min(slotA, slotB), max(slotA, slotB));
}

int Solution::swapGain(size_t slotA, size_t slotB)
{
    if (tardinessAcc[slotA] == tardinessAcc[slotB])
        return 0;

    this->_swap(slotA, slotB);
    int gain = valueGain(min(slotA, slotB), max(slotA, slotB));
    this->_swap(slotA, slotB);

    return gain;
}

void Solution::shift(size_t from, size_t to)
{
    if (tardinessAcc[from] == tardinessAcc[to])
        return;

    this->_shift(from, to);

    updateValue(min(from, to), max(from, to));
}

int Solution::shiftGain(size_t from, size_t to)
{
    if (from == to)
        return 0;

    this->_shift(from, to);
    int gain = valueGain(min(from, to), max(from, to));
    this->_shift(to, from);

    return gain;
}

void Solution::shuffle()
{
    long seed = 0; // std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(scheduling.begin(), scheduling.end(), default_random_engine(seed));

    updateValue(0, instance->numberOfOrders - 1);
}

void Solution::shuffle(default_random_engine &gen)
{
    std::shuffle(scheduling.begin(), scheduling.end(), gen);
    updateValue(0, instance->numberOfOrders - 1);
}

void Solution::copy(const Solution &other)
{
    if (instance->numberOfOrders != other.scheduling.size()) {
        cerr << "Solution::copy: copied solution must be to the same instance" << endl;
        exit(0);
    }

    this->scheduling.assign(other.scheduling.begin(), other.scheduling.end());
    this->timeAcc.assign(other.timeAcc.begin(), other.timeAcc.end());
    this->tardinessAcc.assign(other.tardinessAcc.begin(), other.tardinessAcc.end());
}

void Solution::setScheduling(const vector<unsigned> &scheduling)
{
    this->scheduling.assign(scheduling.begin(), scheduling.end());
    updateValue(0, instance->numberOfOrders - 1);
}

void Solution::perturbBySwap(size_t numberOfSwaps)
{
    // random generator
    long seed = 0; // chrono::system_clock::now().time_since_epoch().count();
    default_random_engine randGenerator(seed);
    // uniform distribution between 0 and swapsPerPerturb
    std::uniform_int_distribution<size_t> randDistribution(0, instance->numberOfOrders - 1);

    size_t minSlot = instance->numberOfOrders - 1;
    size_t maxSlot = 0;

    for (unsigned i = 0; i < numberOfSwaps; i++) {
        size_t slotA =  randDistribution(randGenerator);
        size_t slotB =  randDistribution(randGenerator); //x + Utils.rd.nextInt(2 * W) - W;

        // swap
        this->_swap(slotA, slotB);

        minSlot = min(minSlot, min(slotA, slotB));
        maxSlot = max(maxSlot, max(slotA, slotB));
    }

    updateValue(minSlot, maxSlot);
}

void Solution::perturbByShift(size_t numberOfShifts)
{
    // random generator
    long seed = 0; // chrono::system_clock::now().time_since_epoch().count();
    default_random_engine randGenerator(seed);
    // uniform distribution between 0 and swapsPerPerturb
    uniform_int_distribution<size_t> randDistribution(0, instance->numberOfOrders - 1);

    size_t minSlot = instance->numberOfOrders - 1;
    size_t maxSlot = 0;

    for (unsigned i = 0; i < numberOfShifts; i++) {
        size_t from =  randDistribution(randGenerator);
        size_t to   = randDistribution(randGenerator);

        // swap
        this->_shift(from, to);

        minSlot = min(minSlot, min(from, to));
        maxSlot = max(maxSlot, max(from, to));
    }

    updateValue(minSlot, maxSlot);
}

bool Solution::sameTardAcc(size_t slotA, size_t slotB)
{
    return (tardinessAcc[slotA] == tardinessAcc[slotB]);
}

void Solution::randomize(size_t numOfCand)
{
    // random generator
    long seed = 0; // chrono::system_clock::now().time_since_epoch().count();
    default_random_engine randGenerator(seed);


    for (size_t slot = 0; slot < instance->numberOfOrders; slot++) {
        uniform_int_distribution<size_t> randDistribution(slot,
            min(slot + numOfCand - 1, instance->numberOfOrders - 1));

        size_t next = randDistribution(randGenerator);
        if (next != slot)
            swap(scheduling[slot], scheduling[next]);
    }

    updateValue(0, instance->numberOfOrders - 1);
}

unsigned Solution::getValue()
{
    return tardinessAcc.back();
}

size_t Solution::getNumOfSlots() const
{   
    return instance->numberOfOrders;
}

const Instance* Solution::getInstance() const
{
    return instance;
}

unsigned Solution::getOrder(size_t slot)
{
    return this->scheduling[slot];
}

unsigned Solution::getTardAcc(size_t slot)
{
    return this->tardinessAcc[slot];
}

unsigned Solution::getSlot(size_t order)
{
    for (unsigned slot = 0; slot < scheduling.size(); slot++) {
        if (scheduling[slot] == order)
            return slot;
    }
    return 0;
}

unsigned Solution::getFirstLate()
{
    for (unsigned slot = 0; slot < instance->numberOfOrders; slot++) {
        if (tardinessAcc[slot] > 0) {
            return slot;
        }
    }
    return 0;
}

void Solution::setInstance(const Instance *instance)
{
    this->instance = instance;

    if (this->instance != nullptr) {

        if (scheduling.size() != instance->numberOfOrders) {
            scheduling.resize(instance->numberOfOrders);
            tardinessAcc.resize(instance->numberOfOrders);
            timeAcc.resize(instance->numberOfOrders);
        }

        if (timeAcc.back().size() != instance->numberOfMachines) {
            for (vector<unsigned> &v : timeAcc)
                v.resize(instance->numberOfMachines);
        }

        // initializa a trivial solution
        for (unsigned slot = 0; slot < instance->numberOfOrders; slot++) {
            scheduling[slot] = slot;
        }
        updateValue(0, instance->numberOfOrders - 1);
    }
}

