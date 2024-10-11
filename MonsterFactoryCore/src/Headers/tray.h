#ifndef TRAY_H
#define TRAY_H

#include <iostream>
#include <string>
#include "monster.h" // Asegúrate de tener el archivo de cabecera correcto

using namespace std;

struct TrayNode {
    Monster* monster;
    TrayNode* next;

    TrayNode(Monster* newMonster);
};

struct Tray {
    int capacity;
    int length;

    TrayNode* first;
    TrayNode* last;
    bool inProduction;

    Tray(int _capacity);
    void add(Monster* added);
    Monster* pop();
    bool isComplete();
};

#endif // TRAY_H
