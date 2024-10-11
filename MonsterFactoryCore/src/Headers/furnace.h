#ifndef FURNACE_H
#define FURNACE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "tray.h"  // Cambiar a archivo de cabecera
#include "queues.h"  // Cambiar a archivo de cabecera
#include "logFunctions.h"

using namespace std;

struct Furnace {
    // Tray pointers
    Tray* tray1;
    Tray* tray2;
    Tray* tray3;
    Tray* tray4;

    int time;
    MonsterQueue* toQuality;

    // Constructor
    Furnace(int _time, int cap1, int cap2, int cap3, int cap4, MonsterQueue* _toQuality);

    // Métodos
    bool isComplete();
    void add(Monster* monster);
    void empty();
    void playTray(int tray);
    void stopTray(int tray);
};

#endif // FURNACE_H
