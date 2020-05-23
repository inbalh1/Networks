//
// Created by User on 5/20/2020.
//

#ifndef SIMULATOR_SIMULATOR_H
#define SIMULATOR_SIMULATOR_H

#include "Event.h"
#include "TestStation.h"
#include "utils.h"
#include <vector>
#include <queue>


class Simulator {
public:
    Simulator(double max_running_time, double mu, double lambda,
              int stationsNum, const std::vector<double>& probabilities):
            max_running_time(max_running_time),
            mu(mu),
            lambda(lambda),
            stationsNum(stationsNum),
            totalTimePerClientsAmount(),
            is_time_up(false),
            clock (0.0),
            totalTestedClientsAmount(0),
            quitClientsAmount(0),
            stations(),
            probabilities(probabilities),
            eventQueue (),
            randomVarGen(1/lambda),
            uniformGen(stationsNum)
                            {
                                unsigned long maxClientsInQueue = 0;
                                for (unsigned long i=0; i<probabilities.size(); i++) {
                                    if (probabilities[i] == 0) {
                                        maxClientsInQueue = i;
                                        break;
                                    }
                                }
                                for(int i=0; i<stationsNum; i++) {
                                    TestStation* station = new TestStation(&(*this), mu, clock, maxClientsInQueue);
                                    stations.push_back(station);
                                }

                                for (unsigned long i=0; i<probabilities.size(); i++) {
                                    totalTimePerClientsAmount.push_back(0);
                                }
                            }
    void run ();
    void customerArrival(); // TODO: Implement
    void customerQuitting();
    void customerFinished();
    void  scheduleEvent (Event * newEvent);
    TestStation* getStationUniformly();
    const double max_running_time;
    const double mu;
    const double lambda;
    int stationsNum;
    std::vector<double> totalTimePerClientsAmount;

    // Functions for returning output
    int getTotalTestedClientsAmount();
    int getQuitClientsAmount();
    double getClock();
    std::vector<double> getAverageTimePerClientsAmount();
protected:
    bool is_time_up;
    double clock;
    int totalTestedClientsAmount;
    int quitClientsAmount;

    std::vector<TestStation*> stations;
    std::vector<double> probabilities;
    // TODO: Add RandomVarGenerator;
    // What is container and allocator? should I use them?
    std::priority_queue<Event*,
            std::vector<Event *, std::allocator<Event*> >,
    eventComparator> eventQueue;
    ExponentGen randomVarGen;
    UniformGen uniformGen;
    void runningIteration();






};


#endif //SIMULATOR_SIMULATOR_H
