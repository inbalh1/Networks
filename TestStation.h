//
// Created by User on 5/21/2020.
//

#ifndef SIMULATOR_TESTSTATION_H
#define SIMULATOR_TESTSTATION_H

#include <queue>
#include "Client.h"
#include "utils.h"

class Simulator;

class TestStation {
public:
    TestStation(Simulator* s, double mu, double lastClientTime, unsigned long maxClientsInQueue):
                                            clientsAmount(0), s(s), mu(mu) ,
                                            lastClientTime(lastClientTime),
                                            maxClientsInQueue(maxClientsInQueue),
                                            idle(true), clients(),
                                            randomVarGen(1/mu){

    }
    void handleClient(double time);
    void clientFinished(double time);
    void joinClient(double time);
    int clientsAmount;
private:
    Simulator* s;
    double mu;
    bool idle;
    double sumWaitingTime;
    double sumServiceTime;
    double lastClientTime;
    unsigned long maxClientsInQueue;
    std::queue<Client*> clients;
    ExponentGen randomVarGen;

};


#endif //SIMULATOR_TESTSTATION_H
