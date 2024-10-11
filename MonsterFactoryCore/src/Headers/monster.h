#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

struct Monster {
    long long ID;
    string combination;
    string type;

    time_t timestampCreation;
    time_t timestampBakingStart;
    time_t timestampBakingEnd;
    time_t timestampDelivered;

    int inspector;
    bool quality;

    enum State {
        inProduction,
        inStock,
        delivered,
        reserved,
    };

    State state;

    // Constructor
    Monster(string _type, string _combination, bool _quality);

    // Métodos
    string tostring();
};

#endif // MONSTER_H
