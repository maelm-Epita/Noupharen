#ifndef PROBABILITY_HPP
#define PROBABILITY_HPP

#include <random>
#include <vector>

class Probability{
public:
    float value;
    static std::vector<double> GetDoubleVector(std::vector<Probability>);
    static std::discrete_distribution<size_t> GetDiscreteDistribution(std::vector<Probability>);
};

#endif // PROBABILITY_HPP
