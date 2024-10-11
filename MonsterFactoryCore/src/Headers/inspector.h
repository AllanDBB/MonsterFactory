#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "monster.h"  // Cambiar a archivo de cabecera

using namespace std;

struct Inspector {
    int probability; // 0 to 100 percent
    int time; // in seconds

    // Constructor
    Inspector();

    // Métodos
    Monster* activate(Monster* monster);
    void inspect(Monster* monster, bool activated);
};

#endif // INSPECTOR_H
