//
// Created by natal on 9/29/2024.
//

#include "Cliente.h"
#ifndef ENTREGA_H
#define ENTREGA_H

struct Entrega {
    Almacen * almacen;
    Cliente * primerClienteNormal;
    Cliente * primerClienteEspecial;

    Entrega(Almacen * _almacen) {
        primerClienteNormal = NULL;
        primerClienteEspecial = NULL;
        almacen = _almacen;
    }

    void insertarNormal(Cliente* cliente) {
        if (primerClienteNormal == NULL) {
            primerClienteNormal = cliente;
            escribirEnBitacoraPedidos("["+obtenerTimestamp()+"] " +primerClienteNormal->toString());
            escribirEnBitacoraGeneral("["+obtenerTimestamp()+"] El pedido: " +primerClienteNormal->toString()+ " fue recibido");
        } else {
            Cliente * temp = cliente;
            escribirEnBitacoraPedidos("["+obtenerTimestamp()+"] " +temp->toString());
            escribirEnBitacoraGeneral("["+obtenerTimestamp()+"] El pedido: " +temp->toString()+ " fue recibido");
            temp->siguiente = primerClienteNormal;
            primerClienteNormal = temp;
        }

    }

    void insertarEspecial(Cliente* cliente) {
        if (primerClienteEspecial == NULL) {
            primerClienteEspecial = cliente;
            escribirEnBitacoraPedidos("["+obtenerTimestamp()+"] " +primerClienteEspecial->toString());
            escribirEnBitacoraGeneral("["+obtenerTimestamp()+"] El pedido: " +primerClienteEspecial->toString()+ " fue recibido");
        } else {
            Cliente * temp = cliente;
            escribirEnBitacoraPedidos("["+obtenerTimestamp()+"] " +temp->toString());
            escribirEnBitacoraGeneral("["+obtenerTimestamp()+"] El pedido: " +temp->toString()+ " fue recibido");
            temp->siguiente = primerClienteEspecial;
            primerClienteEspecial = temp;
        }

    }

    void insertar(Cliente * cliente) {
        if (cliente->prioridad == true) {
            insertarEspecial(cliente);
        }
        else {insertarNormal(cliente);}
    }

    void entregarPedidos(Cliente* cliente) {
        Monstruo * temp = cliente->primerMonstruo;
        while (temp != NULL) {
            temp->estado=2; //marcar todos como entregados
            temp = temp->siguiente;
        }
    }

    void encender() {
        Cliente * temp = primerClienteEspecial;
        while (temp != NULL) {
            Monstruo * monstruo = temp->primerMonstruo;
            while (monstruo != NULL) {
                Monstruo * revisando = almacen->primero;
                while (revisando != NULL) {
                    if (revisando->estado==0 && revisando->nombre == monstruo->nombre) {
                        revisando->estado=1; //marcar como reservado
                        monstruo->estado=1;

                        if (temp->revisarPedido() == true) {
                            entregarPedidos(temp);
                            escribirEnBitacoraPedidos("["+obtenerTimestamp()+"] El pedido: "+temp->toString()+ "ha sido entregado.");
                            escribirEnBitacoraGeneral("["+obtenerTimestamp()+"] El pedido: "+temp->toString()+ "ha sido entregado.");
                        }
                        }
                    revisando = revisando->siguiente;
                    }
                monstruo = monstruo->siguiente;
                }
            temp = temp->siguiente;
            }



        Cliente * temp2 = primerClienteNormal;
        while (temp2 != NULL) {
            Monstruo * monstruo = temp2->primerMonstruo;
            while (monstruo != NULL) {
                Monstruo * revisando = almacen->primero;
                while (revisando != NULL) {
                    if (revisando->estado==0 && revisando->nombre == monstruo->nombre) {
                        revisando->estado=1; //marcar como reservado
                        monstruo->estado=1;

                        if (temp2->revisarPedido() == true) {
                            entregarPedidos(temp2);
                            escribirEnBitacoraPedidos("["+obtenerTimestamp()+"] El pedido: "+temp2->toString()+ "ha sido entregado.");
                            escribirEnBitacoraGeneral("["+obtenerTimestamp()+"] El pedido: "+temp2->toString()+ "ha sido entregado.");
                        }
                    }
                    revisando = revisando->siguiente;
                }
                monstruo = monstruo->siguiente;
            }
            temp2 = temp2->siguiente;
        }




    }





    /*void imprimir() {
        Cliente * temp = primerCliente;
        while (temp != NULL) {
            temp->imprimir();
            temp=temp->siguiente;
        }
    }*/
};

#endif //ENTREGA_H
