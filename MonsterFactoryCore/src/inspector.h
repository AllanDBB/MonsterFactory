//
// Created by natal on 9/29/2024.
//
#include "garbageCollector.h"
#include <bits/stdc++.h>
#include "monster.h"

using namespace std;

#ifndef INSPECTOR_H
#define INSPECTOR_H

struct Inspector {
    int probability; // 0 to 100 percent
    int time; // in seconds

    Inspector() {
        probability = 80;
        time = 2;
    }

    Monster* activate(Monster* monster) {
        int pass = rand() % 100;
        if (pass < probability) {
            return monster;
        }

        return nullptr;
    }

    void inspect(Monster* monster, bool activated) {
        if (activated)
            activate(monster);
    }
};

#endif // INSPECTOR_H
