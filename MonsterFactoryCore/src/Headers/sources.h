#ifndef SOURCES_H
#define SOURCES_H

#include <iostream>
#include <string>
#include "material.h" // Asegúrate de tener el archivo de cabecera correcto
#include "queues.h"   // Asegúrate de tener el archivo de cabecera correcto

using namespace std;

struct Source {
    int time;
    bool inProduction;
    MaterialQueue* queue;
    RawMaterials* materials;

    Source(int _time, RawMaterials* _materials, MaterialQueue* _queue);

    void start();
    void stop();
    void produce();
    void changeTime(int _time);
};

#endif // SOURCES_H
