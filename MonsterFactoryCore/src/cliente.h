//
// Created by natal on 9/29/2024.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <bits/stdc++.h>
#include "monster.h"
#include "quality.h"

struct StrNode {
    StrNode* next;
    string name;

    enum State{
        missing,
        delivered,
        reserved,
    };

    State state;

    StrNode(string _name) {
        name = _name;
        state = StrNode::missing;
        next = nullptr;
    }
};

struct Client {
    string name;
    bool priority;
    string orderNumber;
    Client* next;
    StrNode* firstMonster;
    int len;

    Client(string _name, bool _priority, string _orderNumber) {
        name = _name;
        priority = _priority;
        orderNumber = _orderNumber;
        firstMonster = NULL;
        next = NULL;
        len = 0;
    }


    void insert(StrNode* monster) {
        if (firstMonster == nullptr) {
            firstMonster = monster;
        } else {
            StrNode* temp = monster;
            temp->next = firstMonster;
            firstMonster = temp;
        }
        len++;
    }



    bool checkOrder() { // Checks if all the monsters in the order are reserved
        bool complete = true;
        StrNode* temp = firstMonster;
        while (temp != NULL) {
            if (temp->state == StrNode::reserved)
                temp = temp->next;
            else
                complete = false;
        }
        return complete;
    }

    string toString() {
        StrNode* temp = firstMonster;

        string order = "";
        while (temp != NULL) {
            order = order + temp->name + ", ";
            temp = temp->next;
        }
        return "Name: " + name + " Order number: " + (orderNumber) + " Priority: " + (priority ? "With priority" : "Without priority") + " Order: " + order;
    }
};

#endif //CLIENT_H
