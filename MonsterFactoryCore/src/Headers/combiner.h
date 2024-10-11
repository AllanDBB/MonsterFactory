#ifndef COMBINER_H
#define COMBINER_H

#include <iostream>
#include <string>
#include <map>
#include "garbageCollector.h"  // Consider changing this to the header file
#include "logFunctions.h"  // Consider changing this to the header file
#include "monster.h"

using namespace std;


struct Combiner {
    MaterialQueue* material;
    MaterialQueue* energy;
    MaterialQueue* evil;
    MonsterQueue* toBaking;
    GarbageCollector* garbage;
    int time;


    Combiner(MaterialQueue* m, MaterialQueue* e, MaterialQueue* ev, MonsterQueue* _toBaking, GarbageCollector* _garbage);

    string getCombination(const string& _energy, const string& _material, const string& _evil);

    Monster* combine();
};

#endif // COMBINER_H
