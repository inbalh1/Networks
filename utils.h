//
// Created by User on 5/21/2020.
//

#ifndef SIMULATOR_UTILS_H
#define SIMULATOR_UTILS_H

#include <random>
#include <chrono>


class UniformGen {
public:
    UniformGen(int range): range(range), rd(), gen(rd()), dis(0, range - 1) {}
    int generateUniformNum();
private:
    int range;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> dis;
};

class ExponentGen {
public:
    // Construct sets time of event.
    ExponentGen (double lambda) : lambda(lambda), distribution(lambda), generator()
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);

    }
    double nextEvent();
private:
    double lambda;
    std::default_random_engine generator;
    std::exponential_distribution<double> distribution;
};

class ProbabilityGenerator {
public:
    ProbabilityGenerator():
        required_probability(required_probability),
        distribution(0.0,1.0) {}
    bool generateBoolFromProbability(double required_probability);
private:
    double required_probability;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;
};

#endif //SIMULATOR_UTILS_H
