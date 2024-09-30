//
// Created by natal on 9/29/2024.
//

//#include "estructuras.h" , ver funciones de escribir en bitacora y obtener timestamp en el trello

#ifndef COLAMONSTRUOS_H
#define COLAMONSTRUOS_H

struct ColaMonstruo {
    Monstruo *primero;

    ColaMonstruo() {
        primero = NULL;
    }

    bool vacia() {
        if (primero == NULL)
            return true;
        else
            return false;
    }

    void encolar(Monstruo* monstruo) {
        if (vacia())
            primero = monstruo;
        else {
            Monstruo * temp = primero;
            while (temp -> siguiente != NULL) {
                temp = temp -> siguiente;
            }
            Monstruo * nuevo = monstruo;
            nuevo -> siguiente = temp;
        }
    }

    Monstruo* desencolar() {
        if (vacia())
            return NULL;
        else {
            Monstruo * temp = primero;
            primero = primero -> siguiente;
            temp -> siguiente = NULL;
            return temp;
        }
    }


};

#endif //COLAMONSTRUOS_H
