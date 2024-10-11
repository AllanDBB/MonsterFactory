#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include "monster.h" // Asegúrate de que este archivo exista y contenga la definición de Monster
#include "queues.h"
using namespace std;

// Estructura para manejar el almacenamiento de monstruos
struct Storage {
    MonsterNode* first;     // Cabeza de la lista
    int length = 0;
    Storage() : first(nullptr) {} // Constructor que inicializa la lista

    // Inserta un monstruo en el almacenamiento
    void insert(Monster* monster);

    // Busca un monstruo por su tipo y devuelve el nodo correspondiente
    MonsterNode* findMonster(string monsterType);
};

#endif // STORAGE_H
