#ifndef QUEUES_H
#define QUEUES_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "monster.h" // Cambiado de monster.cpp a monster.h para asegurar la declaración de Monster

using namespace std;

struct MaterialNode {
    string data;
    MaterialNode* next;
};

struct MaterialQueue {
    MaterialNode* front;
    MaterialNode* rear;
    int length;
    int capacity;
    MaterialQueue(int);

    void enqueue(string value);
    string dequeue();
    bool isEmpty();
    string peek();
};

struct MonsterNode {
    Monster* monster;
    MonsterNode* next;
    MonsterNode* prev;

    MonsterNode(Monster* _monster);
};

struct MonsterQueue {
    MonsterNode* first;
    int length;
    int capacity;

    MonsterQueue(int);


    bool isEmpty();
    void enqueue(Monster* monster);
    Monster* dequeue();
    string peek();
};

#endif // QUEUES_H
