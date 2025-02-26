#include "include/probability.hpp"

std::vector<double> Probability::GetDoubleVector(std::vector<Probability> pbs){
    std::vector<double> res;
    for (unsigned int i=0; i<pbs.size(); i++){
        res.push_back(pbs[i].value);
    }
    return res;
}

std::discrete_distribution<size_t> Probability::GetDiscreteDistribution(std::vector<Probability> pbs){
    std::vector<double> chance = GetDoubleVector(pbs);
    std::discrete_distribution<size_t> res{chance.begin(), chance.end()};
    return res;
}
