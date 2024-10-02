#include <iostream>
#include <bits/stdc++.h>
// Files:
#include "src/logFunctions.cpp"
#include "src/sources.h"
#include "src/combiner.h"
#include "src/delivery.h"
#include "src/furnace.h"
#include "src/quality.h"

using namespace std;

namespace fs = filesystem;



void readFiles(Delivery * requests) {
    string folder = "MonsterFactoryCore/orders";
    for (const auto& in : fs::directory_iterator(folder)) {
        if (in.is_regular_file()) {
            string path = in.path().string();
            ifstream file(path);
            string line;
            string write = "["+ getTimestamp()+"] The order: ";
            if (file.is_open()) {
                cout << "Leyendo archivo: " << path << endl;
                string name="";
                if (getline(file, line)) {
                    name = line;
                    write += "Name: ";
                    write += name;
                }
                bool priority=false;
                if (getline(file, line)) {
                    write += " Priority: ";
                    if (line == "1st PROGRA") {
                        priority = true;
                        write+= "Yes";

                    }
                    write+= " No";
                }
                string number ="";
                if (getline(file, line)) {
                    number = line;
                    write += " Number: ";
                    write += number;
                }

                write+=" of ";


                while (getline(file, line)) {

                    if (line == "") {
                        break;
                    }
                    Client * client = new Client(name,priority,number);
                    StrNode* monster= new StrNode(line);
                    client->insert(monster);
                    write+= monster->name;
                    write+= ", ";

                    if (priority==true) {
                        requests->PriorityClientQueue->enqueue(client);


                    } else {
                        requests->NormalClientQueue->enqueue(client);
                    }



                };
                writeToGeneralLog(write);
                writeToOrderLog(write);


                file.close();
            } else {
                cerr << "No se pudo abrir el archivo: " << path << endl;
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
    Furnace furnace(10, 2, 2, 2,2, toQuality);
    int i = 0;

    while(i<8) {
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
    Quality quality(storage, garbage, toQuality);

    quality.activate();


    ClientQueue * PriorityClientQueue = new ClientQueue();
    ClientQueue * NormalClientQueue = new ClientQueue();
    Delivery * delivery = new Delivery(storage,NormalClientQueue,PriorityClientQueue);

    readFiles(delivery);
    delivery->activate();







    return 0;
}
