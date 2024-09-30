//
// Created by adbyb on 9/29/2024.
//


#include <bits/stdc++.h>
#include "material.h"


using namespace std;

#ifndef SOURCES_H
#define SOURCES_H

struct Source{


    int time;
    bool inProduction = false;
    // Queue * queue;
    RawMaterials* materials;


    Source(int _time, RawMaterial* material, Queue* queue){
        time = _time;
        RawMaterial = materials;
        // queue = queue;
    }

    void start(){
        inProduction = true;
    }

    void stop(){
        inProduction = false;
    }

        void produce(){

            if (!inProduction)
                return;

            int materialndex = rand() % material.length;

            Material* producedMaterial = returnFromIndex(materialIndex);

            // Add produced material to queue:
            String token = to_string(producedMaterial.index) + " " + producedMaterial.name + " " + materials.className;
            // queue.add(producedMaterial); || queue.add(token) || queue.add(producedMaterial.index);

        }

};


#endif //SOURCES_H
