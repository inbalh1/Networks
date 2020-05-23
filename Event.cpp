//
// Created by User on 5/20/2020.
//

#include "Event.h"
#include "utils.h"
#include "Simulator.h"

void ArrivalEvent::processEvent (Simulator* s) {
    // TODO: choose station, and choose whether or not to quit
    TestStation* station = s->getStationUniformly();
    s->customerArrival();
    bool should_stay;
    if (station->clientsAmount >= probabilities.size()) {
        should_stay = false;
    } else {
        should_stay = gen.generateBoolFromProbability(probabilities[station->clientsAmount]);
    }
    if (should_stay) {
        s->scheduleEvent(new JoinQueueEvent(time, station));
    } else {
        s->scheduleEvent(new QuittingEvent(time));
    }


}
void FinishQueue::processEvent(Simulator* s) {
    s->customerFinished();
    station->clientFinished(time);
}

void QuittingEvent::processEvent(Simulator* s) {
    s->customerQuitting();
}

void JoinQueueEvent::processEvent(Simulator *s) {
    station->joinClient(time);
}
