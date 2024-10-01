//
// Created by natal on 9/29/2024.
//

#include "storage.h"
#include <bits/stdc++.h>
#include "monster.h"
#include "inspector.h"
#include "garbageCollector.h"

#ifndef QUALITY_H
#define QUALITY_H

string getTimestamp() {
    auto ahora = chrono::system_clock::now();
    time_t tiempoActual = chrono::system_clock::to_time_t(ahora);
    tm* fechaHora = localtime(&tiempoActual);
    stringstream ss;
    ss << put_time(fechaHora, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
void writeToStorageLog(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("C:/Users/natal/Desktop/u/2024/segundo semestre/estructuras de datos/bitacoraAlmacen.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}
void writeToInspector1Log(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("C:/Users/natal/Desktop/u/2024/segundo semestre/estructuras de datos/bitacoraInspector1.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}
void writeToInspector2Log(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("C:/Users/natal/Desktop/u/2024/segundo semestre/estructuras de datos/bitacoraInspector2.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}
void writeToGeneralLog(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("C:/Users/natal/Desktop/u/2024/segundo semestre/estructuras de datos/archivo.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}
void writeToGarbageCollectorLog(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("C:/Users/natal/Desktop/u/2024/segundo semestre/estructuras de datos/bitacoraBasurero.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}



struct Quality {
    Inspector* inspector1;
    Inspector* inspector2;
    GarbageCollector* garbageCollector;
    Storage* storage;
    MonsterQueue* monster_queue;

    Quality(Storage* _storage, GarbageCollector* _garbageCollector, MonsterQueue* _monster_queue) {
        inspector1 = new Inspector;
        inspector2 = new Inspector;
        monster_queue = _monster_queue;
        garbageCollector = _garbageCollector;
        storage = _storage;
    }

    bool isEmpty() {
        if (monster_queue->first == NULL)
            return true;
        else
            return false;
    }

    void evaluate(bool activated) {
        if (activated)
            activate();
    }

    Monster* dequeue() {
        if (isEmpty())
            return NULL;
        else {
            MonsterNode* temp = monster_queue->first;
            monster_queue->first = monster_queue->first->next;
            temp->next = NULL;
            return temp->monster;
        }
    }

    void activate() {
        Monster* temp = dequeue();

        while (temp != NULL) {
            if (inspector1->activate(temp) == NULL) {
                garbageCollector->insert(temp);
                writeToInspector1Log("[" + getTimestamp() + "] The monster " +temp->tostring()+ " has been discarded.");
                writeToGarbageCollectorLog("[" + getTimestamp() + "] The monster " +temp->tostring()+ " entered because inspector 1 discarded it.");
                writeToGeneralLog("[" + getTimestamp() + "] The monster " +temp->tostring()+ " entered the garbage collector because inspector 1 discarded it.");
                temp = dequeue();
            } else {
                if (inspector2->activate(temp) == NULL) {
                    garbageCollector->insert(temp);
                    writeToInspector2Log("[" + getTimestamp() + "] The monster " +temp->tostring()+ " has been discarded.");
                    writeToGarbageCollectorLog("[" + getTimestamp() + "] The monster " +temp->tostring()+" entered because inspector 2 discarded it."); // TODO: write it correctly
                    writeToGeneralLog("[" + getTimestamp() + "] The monster " +temp->tostring()+ " entered the garbage collector because inspector 2 discarded it.");
                    temp = dequeue();
                } else {
                    storage->insert(temp);
                    writeToStorageLog("[" + getTimestamp() + "] The monster " +temp->tostring()+ " entered storage and is available for delivery.");
                    writeToGeneralLog("[" + getTimestamp() + "] The monster " +temp->tostring()+ " entered storage and is available for delivery.");
                    temp = dequeue();
                }
            }
        }
    }
};

#endif // QUALITY_H
