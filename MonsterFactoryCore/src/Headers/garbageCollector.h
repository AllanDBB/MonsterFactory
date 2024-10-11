#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H

#include "queues.h"  // Cambiar a archivo de cabecera

using namespace std;

struct GarbageCollector {
    MonsterNode* first;
    MonsterNode* last;
    int length;
    // Constructor
    GarbageCollector();

    // Métodos
    void insert(Monster* monster);
};

#endif // GARBAGECOLLECTOR_H
