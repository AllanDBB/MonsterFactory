#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <vector>

// Asegúrate de que este archivo esté correctamente definido
#include "quality.h"  // Cambiar a archivo de cabecera

using namespace std;

struct StrNode {
    StrNode* next;
    string name;

    enum State {
        missing,
        delivered,
        reserved,
    };

    State state;

    // Constructor
    StrNode(string _name);
};

struct Client {
    string name;
    bool priority;
    string orderNumber;
    Client* next;
    StrNode* firstMonster;
    int len;

    // Constructor
    Client(string _name, bool _priority, string _orderNumber);

    // Métodos
    void insert(StrNode* monster);
    bool checkOrder();
    string toString();
};

#endif // CLIENT_H
