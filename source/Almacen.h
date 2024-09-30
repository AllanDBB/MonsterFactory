//
// Created by natal on 9/29/2024.
//

#ifndef ALMACEN_H
#define ALMACEN_H
#include "Inspector.h"

struct Almacen {
    Monstruo * primero;

    Almacen () {
        primero = NULL;
    }

    void insertar(Monstruo* monstruo) {
        if (primero == NULL) {
            primero = monstruo;
        } else {
            Monstruo * temp = monstruo;
            temp->siguiente = primero;
            primero = temp;
        }

    }
};

#endif //ALMACEN_H
