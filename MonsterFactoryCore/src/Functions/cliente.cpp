#include "../../cliente.h"

StrNode::StrNode(string _name) {
    name = _name;
    state = StrNode::missing;
    next = nullptr;
}

Client::Client(string _name, bool _priority, string _orderNumber) {
    name = _name;
    priority = _priority;
    orderNumber = _orderNumber;
    firstMonster = nullptr;
    next = nullptr;
    len = 0;
}

void Client::insert(StrNode* monster) {
    if (firstMonster == nullptr) {
        firstMonster = monster;
    } else {
        StrNode* temp = monster;
        temp->next = firstMonster;
        firstMonster = temp;
    }
    len++;
}

bool Client::checkOrder() { // Checks if all the monsters in the order are reserved
    StrNode* temp = firstMonster;
    while (temp != NULL) {
        if (temp->state == StrNode::reserved) {
            temp = temp->next;
        } else {
            return false;
        }
    }
    return true;
}

string Client::toString() {
    StrNode* temp = firstMonster;
    string order = "";

    while (temp != NULL) {
        order = order + temp->name + ", ";
        temp = temp->next;
    }
    return "Name: " + name + " Order number: " + orderNumber + " Priority: " + (priority ? "With priority" : "Without priority") + " Order: " + order;
}
