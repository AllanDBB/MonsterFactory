//
// Created by natal on 9/29/2024.
//

#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H

#include "queues.h"

using namespace std;


struct GarbageCollector {
    MonsterNode* first;
    MonsterNode* last;

    GarbageCollector() {
        first = nullptr;
        last = nullptr;
    }

    void insert(Monster* monster) {
        MonsterNode* newNode = new MonsterNode(monster);

        if (last == nullptr) {

            first = newNode;
            last = newNode;
        } else {

            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
    }
};

#endif // GARBAGECOLLECTOR_H
