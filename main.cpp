#include <iostream>
#include <bits/stdc++.h>
// Files:

#include "./source/sources.h"
#include "./source/combiner.h"
#include "./source/furnace.h"

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




    return 0;
}
