//
// Created by adbyb on 9/29/2024.
//


#include <bits/stdc++.h>
#include "monster.h"

using namespace std;

#ifndef QUEUES_H
#define QUEUES_H

struct MaterialNode {
    string data;
    MaterialNode* next;
};

struct MaterialQueue {
    MaterialNode* front;
    MaterialNode* rear;

    MaterialQueue() {
        front = nullptr;
        rear = nullptr;
    }

    void enqueue(string value) {
        MaterialNode* newNode = new MaterialNode();
        newNode->data = value;
        newNode->next = nullptr;

        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    string dequeue() {
        if (isEmpty()) {
            return "";
        }

        MaterialNode* temp = front;
        string value = front->data;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        return value;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    string peek() {
        if (isEmpty()) {
            return "";
        }
        return front->data;
    }
};

struct MonsterNode {

    Monster* monster;
    MonsterNode* next;

    MonsterNode(Monster* _monster) {
        monster = _monster;
        next = nullptr;
    };

};
struct MonsterQueue {
    MonsterNode* first;

    MonsterQueue() {
        first = NULL;
    }

    bool isEmpty() {
        if (first == NULL)
            return true;
        else
            return false;
    }

    void enqueue(Monster* monster) {
        if (isEmpty())
            first = new MonsterNode(monster);
        else {
            MonsterNode* temp = first;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            MonsterNode* newMonster = new MonsterNode(monster);
            newMonster->next = temp;
        }
    }

    Monster* dequeue() {
        if (isEmpty())
            return NULL;
        else {
            MonsterNode* temp = first;
            first = first->next;
            temp->next = NULL;
            return temp->monster;
        }
    }

    string peek() {
        if (isEmpty())
            return "";

        return first->monster->type;
    }
};



#endif //QUEUES_H
