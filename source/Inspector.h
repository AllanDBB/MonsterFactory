//
// Created by natal on 9/29/2024.
//
#include "Basurero.h"
#ifndef INSPECTOR_H
#define INSPECTOR_H

struct Inspector {
    int probabilidad; //0 a 100 porciento
    int tiempo; //en segundos

    Inspector() {
        probabilidad = 50;
        tiempo = 2;
    }

    void inspeccionar(Monstruo * monstruo, bool activado) {
        if (activado)
            encender(monstruo);
    }


    Monstruo* encender(Monstruo* monstruo) {
        int pasar = rand() % 100;
        if (pasar < probabilidad) {
            return monstruo;
        }

        return NULL;
    }




};

#endif //INSPECTOR_H
