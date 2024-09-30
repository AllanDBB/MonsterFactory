//
// Created by natal on 9/29/2024.
//

#include "storage.h"
#include <bits/stdc++.h>
#include "monster.h"
#include "inspector.h"

#ifndef QUALITY_H
#define QUALITY_H


struct Quality {
    Inspector* inspector1;
    Inspector* inspector2;
    GarbageCollector* garbageCollector;
    Storage* storage;
    // Reference to oven that holds the monsters
    Monster* first;

    Quality(Storage* _storage, GarbageCollector* _garbageCollector) {
        inspector1 = new Inspector;
        inspector2 = new Inspector;
        first = NULL;
        garbageCollector = _garbageCollector;
        storage = _storage;
    }

    bool isEmpty() {
        if (first == NULL)
            return true;
        else
            return false;
    }

    void evaluate(bool activated) {
        if (activated)
            activate();
    }

    Monster* dequeue() {
        if (isEmpty())
            return NULL;
        else {
            Monster* temp = first;
            first = first->next;
            temp->next = NULL;
            return temp;
        }
    }

    void activate() {
        Monster* temp = dequeue();

        while (temp != NULL) {
            if (inspector1->activate(temp) == NULL) {
                garbageCollector->insert(temp);
                writeToInspector1Log("[" + getTimestamp() + "] The monster " + to_string(temp->id) + " of type " + temp->name + " has been discarded.");
                writeToGarbageCollectorLog("[" + getTimestamp() + "] The monster " + to_string(temp->id) + " of type " + temp->name + " entered because inspector 1 discarded it.");
                writeToGeneralLog("[" + getTimestamp() + "] The monster " + to_string(temp->id) + " of type " + temp->name + " entered the garbage collector because inspector 1 discarded it.");
                temp = dequeue();
            } else {
                if (inspector2->activate(temp) == NULL) {
                    garbageCollector->insert(temp);
                    writeToInspector2Log("[" + getTimestamp() + "] The monster " + to_string(temp->id) + " of type " + temp->name + " has been discarded.");
                    writeToGarbageCollectorLog("[" + getTimestamp() + "] The monster " + to_string(temp->id) + " of type " + temp->name + " entered because inspector 2 discarded it."); // TODO: write it correctly
                    writeToGeneralLog("[" + getTimestamp() + "] The monster " + to_string(temp->id) + " of type " + temp->name + " entered the garbage collector because inspector 2 discarded it.");
                    temp = dequeue();
                } else {
                    storage->insert(temp);
                    writeToStorageLog("The monster " + to_string(temp->id) + " of type " + temp->name + " entered at " + getTimestamp());
                    writeToGeneralLog("[" + getTimestamp() + "] The monster " + to_string(temp->id) + " of type " + temp->name + " entered storage and is available for delivery.");
                    temp = dequeue();
                }
            }
        }
    }
};

#endif // QUALITY_H
