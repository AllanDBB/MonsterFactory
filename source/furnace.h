//
// Created by adbyb on 9/30/2024.
//


#include <bits/stdc++.h>
#include "monster.h"
#include "tray.h"
#include "queues.h"

using namespace std;

#ifndef FURNACE_H
#define FURNACE_H

struct Furnace{
    // TODO Trays may shut down after baked

    Tray* tray1;
    Tray* tray2;
    Tray* tray3;
    Tray* tray4;

    int time;
    MonsterQueue* toQuality;

    Furnace(int _time, int cap1, int cap2, int cap3, int cap4, MonsterQueue* _toQuality){
        tray1 = new Tray(cap1);
        tray2 = new Tray(cap2);
        tray3 = new Tray(cap3);
        tray4 = new Tray(cap4);
        toQuality = _toQuality;
        time = _time;
    }

    bool isComplete(){
        // Check if should be with . instead of ->.
        return tray1->isComplete() && tray2->isComplete() && tray3->isComplete() && tray4->isComplete();
    }

    void add(Monster* monster){

        if (isComplete())
            return;

        if (!(tray1->isComplete())){
            tray1->add(monster);
            return;
        }

        if (!(tray2->isComplete())){
            tray2->add(monster);
            return;
        }

        if (!(tray3->isComplete())){
            tray3->add(monster);
            return;
        }

        if (!(tray4->isComplete())){
            tray4->add(monster);
            return;
        }
    }

    void empty(){
        Monster* temp;

        while(tray1->length != 0 && tray1->inProduction == true){
            temp = tray1->pop();
            toQuality->enqueue(temp);
        }

        while(tray2->length != 0 && tray2->inProduction == true){
            temp = tray2->pop();
            toQuality->enqueue(temp);
        }
        while(tray3->length != 0 && tray3->inProduction == true){
            temp = tray3->pop();
            toQuality->enqueue(temp);
        }
        while(tray4->length != 0 && tray4->inProduction == true){
            temp = tray4->pop();
            toQuality->enqueue(temp);
        }
    };

    void playTray(int tray){

        switch(tray){
            case 1:
                tray1->inProduction = true;
            case 2:
                tray2->inProduction = true;
            case 3:
                tray3->inProduction = true;
            case 4:
                tray4->inProduction = true;
            default:
               return;
        }
    }
    void stopTray(int tray){

        switch(tray){
            case 1:
                tray1->inProduction = false;
            case 2:
                tray2->inProduction = false;
            case 3:
                tray3->inProduction = false;
            case 4:
                tray4->inProduction = false;
            default:
                return;
        }
    }
};
#endif //FURNACE_H
