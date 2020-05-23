//
// Created by User on 5/21/2020.
//

#include "TestStation.h"
#include "Event.h"
#include <assert.h>
#include "Simulator.h"
#include "utils.h"

void TestStation::handleClient(double time) {
    if (idle && (!clients.empty())) {
        idle = false;
        Client* c = clients.front();
        c->startServiceTime = time;

        double next_departure_time = randomVarGen.nextEvent();
        s->scheduleEvent(new FinishQueue(time + next_departure_time, this));
    }



}

void TestStation::clientFinished(double time) {
    assert(!clients.empty());
    clients.pop();
    assert(clientsAmount>0);
    // Calc time the queue had clientsAmount clients
    s->totalTimePerClientsAmount[clientsAmount] += (time - lastClientTime);
    lastClientTime = time;
    // Update the Station state
    clientsAmount--;
    idle = true;
    handleClient(time);
}

void TestStation::joinClient(double time) {
    // Safety mechanism in case clients will join the queue even with 0 probability
    if (clients.size() == maxClientsInQueue - 1) {
        s->scheduleEvent(new QuittingEvent(time));
    }
    assert(clientsAmount == int(clients.size()));
    // Calc time the queue had clientsAmount clients
    s->totalTimePerClientsAmount[clientsAmount] += (time - lastClientTime);
    lastClientTime = time;
    // Add the new client to queue
    Client* newClilent = new Client(time);
    clients.push(newClilent);
    clientsAmount++;
    // Handle new Client only if he's the only one
    if (idle) {
        assert(clientsAmount==1);
        handleClient(time);
    }
}

