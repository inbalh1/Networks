//
// Created by User on 5/20/2020.
//

#include "Simulator.h"
#include "utils.h"

#include <iostream>




void Simulator::scheduleEvent(Event *newEvent) {
    eventQueue.push (newEvent);
}

void Simulator::runningIteration() {
    // Handle single event
    // TODO: Check if I should keep clear events until arrival event
    // Maybe I should add new arrivals only in arrival event? same for finishing events
    if (!eventQueue.empty ()) {
        Event * nextEvent = eventQueue.top ();
        clock = nextEvent->time;
        eventQueue.pop();
        nextEvent->processEvent (this);
        delete nextEvent;
    }

    if (!is_time_up) {
        double next_arrival_time = randomVarGen.nextEvent();
        if (clock + next_arrival_time >= max_running_time) {
            is_time_up = true;
        } else {
            scheduleEvent(new ArrivalEvent(clock + next_arrival_time, probabilities, stations));
        }
    }

    /*
    for (int i; i<stations.size(); i++) {
        stations[i]->handleClient();
    }*/


}


void Simulator::run () {
    if(!probabilities.empty()) {


        // Run until time is up
        while (!is_time_up) {
            runningIteration();

        }
        // Keep running to make sure all the pending customers will finish
        while (!eventQueue.empty()) {
            runningIteration();
        }

        //TODO: Return relevant parameters:
        // totalTestedClientsAmount, quitClientsAmount, time
    }

}

void Simulator::customerArrival() {
}

void Simulator::customerFinished() {
    totalTestedClientsAmount++;
}

void Simulator::customerQuitting() {
    quitClientsAmount++;
}

TestStation *Simulator::getStationUniformly() {
    int stationNum  = uniformGen.generateUniformNum();
    return stations[stationNum];
}

int Simulator::getTotalTestedClientsAmount() {
    return totalTestedClientsAmount;
}

int Simulator::getQuitClientsAmount() {
    return quitClientsAmount;
}

double Simulator::getClock() {
    return clock;
}

std::vector<double> Simulator::getAverageTimePerClientsAmount() {
    for(double & i : totalTimePerClientsAmount) {
        i = i / double(stationsNum);
    }
    return totalTimePerClientsAmount;
}
