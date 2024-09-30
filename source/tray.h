//
// Created by adbyb on 9/30/2024.
//


#include <bits/stdc++.h>
#include "monster.h"

using namespace std;


#ifndef TRAY_H
#define TRAY_H

struct TrayNode{

    Monster* monster;
    TrayNode* next;

    TrayNode(Monster* newMonster){
        monster = newMonster;
        next = nullptr;
    }


};
struct Tray{

    int capacity;
    int length;
    TrayNode* first;
    TrayNode* last;
    bool inProduction;

    Tray(int _capacity){
        capacity = _capacity;
        length = 0;
        first = nullptr;
        last = nullptr;
        inProduction = true;
    }

    void add(Monster* added){
        if (length == 0)
            first = last = new TrayNode(added);

        if (length == 1){
            TrayNode * temp = new TrayNode(added);
            first->next = temp;
            last = temp;
        } else {
            TrayNode * temp = new TrayNode(added);
            last->next = temp;
            last = temp;
        }
        length++;
    }

    Monster * pop(){
        TrayNode* temp = first;
        first = temp->next;
        length--;
        return temp->monster;
    }

    bool isComplete(){
        return capacity == length;
    }

};
#endif //TRAY_H
