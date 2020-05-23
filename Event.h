//
// Created by User on 5/20/2020.
//

#ifndef SIMULATOR_EVENT_H
#define SIMULATOR_EVENT_H

#include <vector>
#include "TestStation.h"
#include "utils.h"

class Simulator;

class Event {
    public:
        // Construct sets time of event.
        Event (double t) : time (t)
        { }
        // Execute event by invoking this method.
        virtual void processEvent (Simulator* s) = 0;

        const double time;
};

struct eventComparator {
    bool operator() (const Event * left, const Event * right) const {
        return left->time > right->time;
    }
};

class ArrivalEvent : public Event {
public:
    ArrivalEvent (double t, std::vector<double> &probabilities, std::vector<TestStation*> &stations)
            : probabilities(probabilities), stations(stations), gen(), Event (t)
    { }
    ~ArrivalEvent();
    void processEvent (Simulator* s);

private:
    std::vector<double>& probabilities;
    std::vector<TestStation*>& stations;
    ProbabilityGenerator gen;
};

class FinishQueue : public Event {
public:
    FinishQueue (double t, TestStation* station)
            : station(station), Event (t)
    { }
    ~FinishQueue();
    virtual void processEvent (Simulator* s);

private:
    TestStation* station;
};

class JoinQueueEvent : public Event {
public:
    JoinQueueEvent (double t, TestStation* station)
            : station(station), Event (t)
    { }
    ~JoinQueueEvent();
    virtual void processEvent (Simulator* s);
private:
    TestStation* station;
};

class QuittingEvent : public Event {
public:
    QuittingEvent (double t)
            : Event (t)
    { }
    ~QuittingEvent();
    virtual void processEvent (Simulator* s);
};

#endif //SIMULATOR_EVENT_H
