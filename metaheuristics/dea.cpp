#include "dea.h"

bool compSolutions(Solution *s1, Solution *s2) {
    return s1->getValue() < s2->getValue();
}

bool auxComp(pair<double, unsigned> &a, pair<double, unsigned> &b) {
    return a.first < b.first;
}

DEA::DEA(unsigned popSize, double eliteRatio, double alpha,
         unsigned iteration, const Instance* inst):
    OptimizationMethod(inst), popSize(popSize),
    alpha(alpha), iteration(iteration)
{
    this->eliteSize = unsigned(max(1., round(popSize * eliteRatio)));

    unsigned long seed = 0;//chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
}

void DEA::_run()
{
    vector<double> mean(solution.getNumOfSlots(), solution.getNumOfSlots()/2.);
    vector<double> stddev(solution.getNumOfSlots(), solution.getNumOfSlots() * .5);
    vector<Solution*> elite(eliteSize, nullptr);

    for (unsigned i = 0; i < iteration; i++) {
        sample(elite, mean, stddev);

        // update best solution
        Solution *best = &this->solution;
        for (Solution *s : elite) {
            if (s->getValue() < best->getValue())
                best = s;
        }
        if (best != &this->solution) {
            this->solution.copy(*best);
            cout << i << " " << this->solution.getValue() << endl;
        }

        update(elite, mean, stddev);

        for (Solution *s : elite) {
            delete s;
        }
    }

}

Solution *DEA::newSample(vector<double> &mean, vector<double> &stddev)
{
    vector<pair<double, unsigned>> auxVec;

    for (unsigned i = 0; i < solution.getNumOfSlots(); i++) {
        normal_distribution<double> distri(mean[i], stddev[i]);
        auxVec.push_back(make_pair(distri(generator), i));
    }

    sort(auxVec.begin(), auxVec.end());
    vector<unsigned> schedule(solution.getNumOfSlots());
    for (unsigned i = 0; i < solution.getNumOfSlots(); ++i) {
        schedule[i] = auxVec[i].second;
    }

    Solution *s = new Solution(solution.getInstance());
    s->setScheduling(schedule);
    return s;
}

void DEA::sample(vector<Solution*> &elite, vector<double> &mean, vector<double> &stddev)
{
    unsigned counter = 0;
    for (unsigned i = 0; i < popSize; i++) {
        Solution *ns = newSample(mean, stddev);
        if (counter < eliteSize) {
            elite[counter++] = ns;
            push_heap(elite.begin(), elite.begin() + counter, compSolutions);
        } else {
            if (ns->getValue() < elite.front()->getValue()) {
                pop_heap(elite.begin(), elite.end(), compSolutions);
                delete elite.back();
                elite.back() = ns;
                push_heap(elite.begin(), elite.end(), compSolutions);
            }
        }
    }
}

void DEA::update(vector<Solution *> &elite, vector<double> &mean, vector<double> &stddev)
{
    vector<double> _mean(solution.getNumOfSlots(), 0.);
    vector<double> _stddev(solution.getNumOfSlots(), 0.);

    for (Solution *s : elite)
        for (unsigned i = 0; i < solution.getNumOfSlots(); i++)
            _mean[i] += s->getSlot(i);
    for (double &m : _mean)
        m /= elite.size();

    for (Solution *s : elite)
        for (unsigned i = 0; i < solution.getNumOfSlots(); i++)
            _stddev[i] += pow(s->getSlot(i) - _mean[i], 2);
    for (double &m : _stddev)
        m = sqrt(m / elite.size());

    for (unsigned i = 0; i < solution.getNumOfSlots(); i++) {
        mean[i] = mean[i] * (1. - alpha) + _mean[i] * alpha;
        stddev[i] = stddev[i] * (1. - alpha) + _stddev[i] * alpha;
    }
}


