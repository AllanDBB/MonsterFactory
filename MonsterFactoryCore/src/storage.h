//
// Created by natal on 9/29/2024.
//

#ifndef STORAGE_H
#define STORAGE_H

#include <bits/stdc++.h>
#include "monster.h"
#include "tray.h"
#include "queues.h"

using namespace std;

#include "inspector.h"

struct Storage {
    MonsterNode* first;

    Storage() {
        first = NULL;
    }

    void insert(Monster* monster) {
        if (first == NULL) {
            first = new MonsterNode(monster);
            first->monster->state= Monster::inStock;
        } else {
            MonsterNode* temp = new MonsterNode(monster);
            temp->monster->state= Monster::inStock;
            temp->next = first;
            first = temp;
        }
    }

    MonsterNode* findMonster(string monster) {
        MonsterNode * temp = first;
        while (temp != NULL) {
            if (temp->monster->type == monster && temp->monster->state == Monster::inStock) {
                return temp;
            }
            temp = temp->next;

        }
        return NULL;
    }
};

#endif // STORAGE_H
