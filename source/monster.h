//
// Created by adbyb on 9/29/2024.
//


#include <bits/stdc++.h>
#include <chrono>

using namespace std;
#ifndef MONSTER_H
#define MONSTER_H

struct Monster{

    int ID; // m1-m2-m3-dd-mm-hh
    String combination;
    time_t timestampCreation;
    String type;
    time_t timestampBakingStart;
    time_t timestampBakingEnd;
    //Tray * tray;
    int inspector;
    bool approved;
    bool inStock;


};
#endif //MONSTER_H
