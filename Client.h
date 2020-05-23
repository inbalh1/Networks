//
// Created by User on 5/21/2020.
//

#ifndef SIMULATOR_CLIENT_H
#define SIMULATOR_CLIENT_H


class Client {
public:
    Client(double arrivalTime) : arrivalTime(arrivalTime),
                                 startServiceTime(-1) {}

    double arrivalTime;
    double startServiceTime;

};


#endif //SIMULATOR_CLIENT_H
