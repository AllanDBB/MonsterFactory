//
// Created by natal on 10/1/2024.
//
using namespace std;
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

void writeToOrderLog(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("MonsterFactoryCore/logs/BitacoraPedidos.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}
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

    bitacora.open("MonsterFactoryCore/logs/BitacoraAlmacen.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}
void writeToInspector1Log(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("MonsterFactoryCore/logs/BitacoraInspector1.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}
void writeToInspector2Log(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("MonsterFactoryCore/logs/BitacoraInspector2.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}
void writeToGeneralLog(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("MonsterFactoryCore/logs/BitacoraGeneral.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}
void writeToGarbageCollectorLog(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("MonsterFactoryCore/logs/BitacoraBasurero.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}
void writeToDelivery(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("MonsterFactoryCore/logs/BitacoraEntrega.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}

void writeToQueue(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("MonsterFactoryCore/logs/BitacoraCola.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}
void writeToFurnace(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("MonsterFactoryCore/logs/BitacoraHorno.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}