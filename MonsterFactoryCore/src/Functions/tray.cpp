#include "../../tray.h"

TrayNode::TrayNode(Monster* newMonster) {
    monster = newMonster;
    next = nullptr;
}

Tray::Tray(int _capacity) {
    capacity = _capacity;
    length = 0;
    first = nullptr;
    last = nullptr;
    inProduction = true;
}

void Tray::add(Monster* added) {
    if (length == 0) {
        first = last = new TrayNode(added);
    } else {
        TrayNode* temp = new TrayNode(added);
        last->next = temp;
        last = temp;
    }
    length++;
}

Monster* Tray::pop() {
    if (length == 0) {
        return nullptr; // Retorna nullptr si la bandeja está vacía
    }

    TrayNode* temp = first;
    first = first->next;
    length--;

    // Si la bandeja queda vacía, también actualizamos el puntero last
    if (length == 0) {
        last = nullptr;
    }

    return temp->monster;
}

bool Tray::isComplete() {
    if (!inProduction)
        return true;

    return capacity == length;
}
