//
// Created by natal on 9/29/2024.
//

#ifndef CLIENTE_H
#define CLIENTE_H
#include "Calidad.h"

struct Cliente {
    string nombre;
    bool prioridad;
    int numPedido;
    Cliente * siguiente;
    Monstruo * primerMonstruo;


    Cliente(string _nombre, bool _prioridad, int _numPedido) {
        nombre = _nombre;
        prioridad = _prioridad;
        numPedido = _numPedido;
        primerMonstruo = NULL;
        siguiente = NULL;
    };

    void insertar(Monstruo* monstruo) {
        if (primerMonstruo == NULL) {
            primerMonstruo = monstruo;
        } else {
            Monstruo * temp = monstruo;
            temp->siguiente = primerMonstruo;
            primerMonstruo = temp;
        }

    }

    bool revisarPedido() { //revisa que todos los monstruos del pedido estén reservados
        bool completo = true;
        Monstruo * temp = primerMonstruo;
        while (temp != NULL) {
            if (temp->estado==1)
                temp = temp->siguiente;
            else
                completo = false;
        }

        return completo;
    }

    string toString() {
        Monstruo * temp = primerMonstruo;
        string pedido = "";
        while (temp != NULL) {
            pedido=pedido+temp->nombre+", ";
            temp=temp->siguiente;
        }
        return "Nombre: "+nombre+ " Número de pedido: "+to_string(numPedido) +" Prioridad: "+ (prioridad?"Con prioridad":"Sin prioridad")+ " Pedido: " + pedido;
    }
};

#endif //CLIENTE_H
