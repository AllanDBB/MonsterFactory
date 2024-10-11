#include "../../inspector.h"
#include <cstdlib>
#include <ctime>

Inspector::Inspector() {
    probability = 90;
    time = 2;
}

Monster* Inspector::activate(Monster* monster) {
    int pass = rand() % 100;
    if (pass < probability) {
        return monster;
    }
    return nullptr;
}

void Inspector::inspect(Monster* monster, bool activated) {
    if (activated) {
        activate(monster);
    }
}
