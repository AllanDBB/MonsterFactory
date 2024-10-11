#include "../../quality.h"
#include "../../inspector.h"
#include "../../garbageCollector.h"
#include "../../logFunctions.h"
#include <QDebug>
Quality::Quality(Storage* _storage, GarbageCollector* _garbageCollector, MonsterQueue* _monster_queue) {
    inspector1 = new Inspector;
    inspector2 = new Inspector;
    monster_queue = _monster_queue;
    garbageCollector = _garbageCollector;
    storage = _storage;
    active = true;
}

bool Quality::isEmpty() {
    return monster_queue->first == nullptr;
}

void Quality::evaluate(bool activated) {
    if (activated)
        active = true;
    else
        active = false;
}

void Quality::activate() {
    if (active){
    Monster* temp = monster_queue->dequeue();
    writeToQueueLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(temp->tostring()) + " was dequeued.");
    writeToGeneralLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(temp->tostring()) + " was dequeued.");

    while (temp != nullptr) {
        if (inspector1->activate(temp) == nullptr) {
            garbageCollector->insert(temp);
            writeToInspector1Log("[" + getTimestamp() + "] The monster " + QString::fromStdString(temp->tostring()) + " has been discarded.");
            writeToGarbageCollectorLog("[" + getTimestamp() + "] The monster " + QString::fromStdString(temp->tostring()) + " entered because inspector 1 discarded it.");
            writeToGeneralLog("[" + getTimestamp() + "] The monster " + QString::fromStdString(temp->tostring()) + " entered the garbage collector because inspector 1 discarded it.");
            temp = monster_queue->dequeue();

         } else {
            if (inspector2->activate(temp) == nullptr) {
                garbageCollector->insert(temp);
                writeToInspector2Log("[" + getTimestamp() + "] The monster " + QString::fromStdString(temp->tostring()) + " has been discarded.");
                writeToGarbageCollectorLog("[" + getTimestamp() + "] The monster " + QString::fromStdString(temp->tostring()) + " entered because inspector 2 discarded it.");
                writeToGeneralLog("[" + getTimestamp() + "] The monster " + QString::fromStdString(temp->tostring()) + " entered the garbage collector because inspector 2 discarded it.");
                temp = monster_queue->dequeue();

            } else {
                storage->insert(temp);
                writeToStorageLog("[" + getTimestamp() + "] The monster " + QString::fromStdString(temp->tostring()) + " entered storage and is available for delivery.");
                writeToGeneralLog("[" + getTimestamp() + "] The monster " + QString::fromStdString(temp->tostring()) + " entered storage and is available for delivery.");
                temp = monster_queue->dequeue();

            }
        }
    }
    }
}
