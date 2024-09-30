//
// Created by adbyb on 9/29/2024.
//


#include <bits/stdc++.h>
#include "material.h"
#include "queues.h"

using namespace std;

#ifndef SOURCES_H
#define SOURCES_H

struct Source{


    int time;
    bool inProduction = false;
    MaterialQueue * queue;
    RawMaterials* materials;


    Source(int _time, RawMaterials* _materials, MaterialQueue* _queue){
        time = _time;
        materials = _materials;
        queue = _queue;
    }

    void start(){
        inProduction = true;
    }

    void stop(){
        inProduction = false;
    }

    void produce() {
        if (!inProduction)
            return;

        int materialIndex = rand() % materials->length; // ¡! TODO. Why only says 2.
        
        Material* producedMaterial = materials->returnFromIndex(materialIndex);

        string token = to_string(producedMaterial->index) + " " + producedMaterial->name + " " + materials->className;
        queue->enqueue(producedMaterial->name);
    }

};


#endif //SOURCES_H
