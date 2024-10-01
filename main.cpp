#include <iostream>
#include <bits/stdc++.h>
// Files:

#include "sources.h"
#include "combiner.h"
#include "delivery.h"
#include "furnace.h"
#include "quality.h"

string getTraits(string s) {
    if (s == "INTELIGENCIA") {
        return "Cósmica, Orgánico, Astuta";
    } else if (s == "DESTRUCCION") {
        return "Elemental, Radioactivo, Caótica";
    } else if (s == "REGENERACION") {
        return "Oscura, Orgánico, Despiadada";
    } else if (s == "FUERZA") {
        return "Elemental, Metálico, Despiadada";
    } else if (s == "MALDAD") {
        return "Oscura, Metálico, Astuta";
    } else if (s == "VENENO") {
        return "Oscura, Radioactivo, Despiadada";
    } else if (s == "LOCURA") {
        return "Cósmica, Radioactivo, Caótica";
    } else if (s == "TECNOLOGIA") {
        return "Cósmica, Metálico, Astuta";
    } else if (s == "VELOCIDAD") {
        return "Elemental, Orgánico, Caótica";
    } else {
        return "Unknown trait";
    }
}


namespace fs = filesystem;

int m=1;
int n=1;
void leerArchivos(Delivery * pedidos) {
    string carpeta = "C:/Users/natal/Desktop/u/2024/segundo semestre/estructuras de datos/pedidos";
    for (const auto& entrada : fs::directory_iterator(carpeta)) {
        if (entrada.is_regular_file()) {
            string rutaArchivo = entrada.path().string();
            ifstream archivo(rutaArchivo);
            string linea;

            if (archivo.is_open()) {
                cout << "Leyendo archivo: " << rutaArchivo << endl;
                string nombre="";
                if (getline(archivo, linea)) {
                    nombre = linea;
                }
                bool prioridad=false;
                if (getline(archivo, linea)) {
                    if (linea == "1st PROGRA") {
                        prioridad = true;
                    }
                }

                Client * cliente1 = new Client(nombre,prioridad,n);

                n++;

                while (getline(archivo, linea)) {

                    if (linea == "") {
                        break;
                    }

                    Monster * nuevo = new Monster(linea,getTraits(linea),prioridad);

                    m++;
                    cliente1->insert(nuevo);
                };

                pedidos->insert(cliente1);
                archivo.close();
            } else {
                cerr << "No se pudo abrir el archivo: " << rutaArchivo << endl;
            }

            cout << "---------------------" << endl;
        }
    }
}


int main() {
    srand(time(0));
    // Creation of Raw Materials.
    // TODO. HAY UN ERROR CUANDO EL TIPO NO ES EL MISMO
    RawMaterials* material = new RawMaterials(0, "Material");
    RawMaterials* energy = new RawMaterials(1, "Energía");
    RawMaterials* evil = new RawMaterials(2, "Maldad");

    energy->addMaterial(1, "Oscura", "..");
    energy->addMaterial(1, "Cósmica", "..");
    energy->addMaterial(1, "Elemental", "..");

    material->addMaterial(0, "Orgánico", "..");
    material->addMaterial(0, "Metálico", "..");
    material->addMaterial(0, "Radioactivo", "..");

    evil->addMaterial(2, "Despiadada", "..");
    evil->addMaterial(2, "Astuta", "..");
    evil->addMaterial(2, "Caótica", "..");

    MaterialQueue* materialQueue = new MaterialQueue();
    MaterialQueue* energyQueue = new MaterialQueue();
    MaterialQueue* evilQueue = new MaterialQueue();

    Source materialSource(10, material, materialQueue);
    Source energySource(10, energy, energyQueue);
    Source evilSource(10, evil, evilQueue);

    materialSource.start();
    energySource.start();
    evilSource.start();

    // TODO. It must work with timers.
    //materialSource.produce();
    //energySource.produce();
    //evilSource.produce();

    //cout << materialQueue->peek() << endl;
    //cout << energyQueue->peek() << endl;
    //cout << evilQueue->peek() << endl;

    MonsterQueue* queueToBaking = new MonsterQueue();
    GarbageCollector* monsterGarbage = new GarbageCollector(); // TODO. Shoud be object.

    Combiner combiner(materialQueue, energyQueue, evilQueue, queueToBaking, monsterGarbage);
    //Monster* temp = combiner.combine();
    //cout << temp->type;

    MonsterQueue* toQuality = new MonsterQueue();
    Furnace furnace(10, 1, 1, 1,1, toQuality);
    int i = 0;

    while(i<4) {
        materialSource.produce();
        energySource.produce();
        evilSource.produce();

        combiner.combine();
        if (queueToBaking->peek() != "BUENO" && !queueToBaking->isEmpty()){
            i++;

            furnace.add(queueToBaking->dequeue());

        }
    }

    furnace.playTray(1);
    furnace.playTray(2);
    furnace.playTray(3);
    furnace.playTray(4);

    furnace.empty();


    Storage * storage = new Storage();
    GarbageCollector * garbage = new GarbageCollector();
    Quality * quality = new Quality(storage, garbage, toQuality);

    quality->activate();

    Delivery * delivery = new Delivery(storage);
    leerArchivos(delivery);
    delivery->activate();







    return 0;
}
