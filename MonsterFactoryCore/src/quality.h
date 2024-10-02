//
// Created by natal on 9/29/2024.
//

#include "storage.h"
#include <bits/stdc++.h>
#include "monster.h"
#include "inspector.h"
#include "garbageCollector.h"

#ifndef QUALITY_H
#define QUALITY_H





struct Quality {
    Inspector* inspector1;
    Inspector* inspector2;
    GarbageCollector* garbageCollector;
    Storage* storage;
    MonsterQueue* monster_queue;

    Quality(Storage* _storage, GarbageCollector* _garbageCollector, MonsterQueue* _monster_queue) {
        inspector1 = new Inspector;
        inspector2 = new Inspector;
        monster_queue = _monster_queue;
        garbageCollector = _garbageCollector;
        storage = _storage;
    }

    bool isEmpty() {
        if (monster_queue->first == nullptr)
            return true;
        else
            return false;
    }

    void evaluate(bool activated) {
        if (activated)
            activate();
    }



    void activate() {
        Monster* temp = monster_queue->dequeue();
        writeToQueue("["+getTimestamp()+"] Monster "+temp->tostring()+" was dequeued.");
        writeToGeneralLog("["+getTimestamp()+"] Monster "+temp->tostring()+" was dequeued.");

        while (temp != nullptr) {
            if (inspector1->activate(temp) == nullptr) {
                garbageCollector->insert(temp);
                writeToInspector1Log("[" + getTimestamp() + "] The monster " +temp->tostring()+ " has been discarded.");
                writeToGarbageCollectorLog("[" + getTimestamp() + "] The monster " +temp->tostring()+ " entered because inspector 1 discarded it.");
                writeToGeneralLog("[" + getTimestamp() + "] The monster " +temp->tostring()+ " entered the garbage collector because inspector 1 discarded it.");
                temp = monster_queue->dequeue();
            } else {
                if (inspector2->activate(temp) == nullptr) {
                    garbageCollector->insert(temp);
                    writeToInspector2Log("[" + getTimestamp() + "] The monster " +temp->tostring()+ " has been discarded.");
                    writeToGarbageCollectorLog("[" + getTimestamp() + "] The monster " +temp->tostring()+" entered because inspector 2 discarded it."); // TODO: write it correctly
                    writeToGeneralLog("[" + getTimestamp() + "] The monster " +temp->tostring()+ " entered the garbage collector because inspector 2 discarded it.");
                    temp = monster_queue->dequeue();
                } else {
                    storage->insert(temp);
                    writeToStorageLog("[" + getTimestamp() + "] The monster " +temp->tostring()+ " entered storage and is available for delivery.");
                    writeToGeneralLog("[" + getTimestamp() + "] The monster " +temp->tostring()+ " entered storage and is available for delivery.");
                    temp = monster_queue->dequeue();
                }
            }
        }
    }
};

#endif // QUALITY_H
