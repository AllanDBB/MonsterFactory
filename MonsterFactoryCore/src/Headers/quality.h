#ifndef QUALITY_H
#define QUALITY_H

#include "inspector.h"
#include "garbageCollector.h"
#include "storage.h"
#include <iostream>
#include <string>

struct Quality {
    Inspector* inspector1;
    Inspector* inspector2;
    GarbageCollector* garbageCollector;
    Storage* storage;
    MonsterQueue* monster_queue;
    bool active;

    // Constructor
    Quality(Storage* _storage, GarbageCollector* _garbageCollector, MonsterQueue* _monster_queue);

    // Métodos
    bool isEmpty();
    void evaluate(bool activated);
    void activate();
};

#endif // QUALITY_H
