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
    Monster* first;

    Storage() {
        first = NULL;
    }

    void insert(Monster* monster) {
        if (first == NULL) {
            first = monster;
        } else {
            Monster* temp = monster;
            temp->next = first;
            first = temp;
        }
    }
};

#endif // STORAGE_H
