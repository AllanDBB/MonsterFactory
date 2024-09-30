//
// Created by natal on 9/29/2024.
//

#ifndef CALIDAD_H
#define CALIDAD_H
#include "Almacen.h"

struct Calidad {
    Inspector * inspector1;
    Inspector * inspector2;
    Basurero * basurero;
    Almacen * almacen;
    //ref a horno que tiene los monstruos
    Monstruo * primero;


    Calidad(Almacen * _almacen, Basurero * _basurero) {
        inspector1 = new Inspector;
        inspector2 =  new Inspector;
        primero = NULL;
        basurero = _basurero;
        almacen = _almacen;
    }

    bool vacia() {
        if (primero == NULL)
            return true;
        else
            return false;
    }

    void evaluar(bool activado) {
        if (activado)
            encender();
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



    void encender() {
        Monstruo * temp = desencolar();

        while (temp!=NULL) {


            if (inspector1->encender(temp)==NULL) {
                basurero->insertar(temp);
                escribirEnBitacoraInspector1("["+obtenerTimestamp()+"] El monstruo "+ to_string(temp->id)+" de tipo " + temp->nombre+" ha sido descartado.");
                escribirEnBitacoraBasurero("["+obtenerTimestamp()+"] El monstruo "+ to_string(temp->id)+" de tipo " + temp->nombre+" ha ingresado porque el inspector 1 lo descartó");
                escribirEnBitacoraGeneral("["+obtenerTimestamp()+"] El monstruo "+ to_string(temp->id)+" de tipo "+temp->nombre+ " ingresó al basurero porque el inspector 1 lo descartó.");
                temp = desencolar();

            } else {
                if (inspector2->encender(temp)==NULL) {
                    basurero->insertar(temp);
                    escribirEnBitacoraInspector2("["+obtenerTimestamp()+"] El monstruo "+ to_string(temp->id)+" de tipo " + temp->nombre+" ha sido descartado.");
                    escribirEnBitacoraBasurero("["+obtenerTimestamp()+"] El monstruo "+ to_string(temp->id)+" de tipo " + temp->nombre+" ha ingresado porque el inspector 2 lo descartó"); //TODO: escribirlo como se debe
                    escribirEnBitacoraGeneral("["+obtenerTimestamp()+"] El monstruo "+ to_string(temp->id)+" de tipo "+temp->nombre+ " ingresó al basurero porque el inspector 2 lo descartó.");
                    temp = desencolar();

                } else {
                    almacen->insertar(temp);
                    escribirEnBitacoraAlmacen("El monstruo "+ to_string(temp->id)+" de tipo " + temp->nombre+" ha ingresado a las " + obtenerTimestamp());
                    escribirEnBitacoraGeneral("["+obtenerTimestamp()+"] El monstruo "+ to_string(temp->id)+" de tipo "+temp->nombre+ " ingresó al almacen y se encuentra disponible para entrega.");
                    temp = desencolar();

                }

            }

        }
    }



};

#endif //CALIDAD_H
