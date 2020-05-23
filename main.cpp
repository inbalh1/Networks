#include <iostream>
#include <vector>
#include "Simulator.h"


int main() {
    // //TODO: Parse input
    double max_running_time = 1000;
    double mu = 25;
    double lambda = 40;
    int servers_num = 2;
    std::vector<double> probabilities;
    probabilities.push_back(1);
    probabilities.push_back(0);
    Simulator simulator(max_running_time, mu, lambda, servers_num, probabilities);
    simulator.run();
    std::cout << simulator.getTotalTestedClientsAmount() << " ";
    std::cout << simulator.getQuitClientsAmount()<< " ";
    std::cout << simulator.getClock() <<" ";
    std::vector<double> averageTimePerClientsAmount = simulator.getAverageTimePerClientsAmount();
    for (double i : averageTimePerClientsAmount) {
        std::cout << i << " ";
    }

    return 0;
}