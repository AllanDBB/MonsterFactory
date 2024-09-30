//
// Created by natal on 9/29/2024.
//

#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H

#include "queues.h"

using namespace std;

struct GarbageCollector {
    MonsterNode* first;

    GarbageCollector() {
        first = nullptr;
    }

    void insert(Monster* monster) {
        if (first == nullptr) {
            first = new MonsterNode(monster);
        } else {
            MonsterNode* temp = new MonsterNode(monster);
            temp->next = first;
            first = temp;
        }
    }
};

#endif // GARBAGECOLLECTOR_H
