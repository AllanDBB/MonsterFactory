//
// Created by natal on 9/29/2024.
//

#ifndef BASURERO_H
#define BASURERO_H
#include "ColaMonstruos.h"

struct Basurero { //??
    Monstruo * primero;

    Basurero() {
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

#endif //BASURERO_H
