//
// Created by User on 5/21/2020.
//


#include <random>
#include <chrono>
#include "utils.h"

/*
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
double ran_expo(double lambda){
    double u;

    u = rand() / (RAND_MAX + 1.0);

    return -log(1- u) / lambda;
}
*/

// last_arrival should start with 0
// Generate numbers in poisson distribution
/*
double next_event(double last_event, double lambda) {
    return last_event + ran_expo(1/lambda);
}
*/
int UniformGen::generateUniformNum() {
    return dis(gen);
}

bool ProbabilityGenerator::generateBoolFromProbability(double required_probability){
    double num = distribution(generator);
    if (num < required_probability) {
        return true;
    } else {
        return false;
    }
}



// Generate numbers in exponential distribution
double ExponentGen::nextEvent(){

    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //std::default_random_engine generator (seed);

    //std::exponential_distribution<double> distribution (lambda);
    double next_event = distribution(generator);
    return next_event;
}