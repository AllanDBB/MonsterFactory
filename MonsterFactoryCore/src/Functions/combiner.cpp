#include "../../combiner.h"
#include <QDebug>
Combiner::Combiner(MaterialQueue* m, MaterialQueue* e, MaterialQueue* ev, MonsterQueue* _toBaking, GarbageCollector* _garbage) {
    material = m;
    energy = e;
    evil = ev;
    toBaking = _toBaking;
    garbage = _garbage;
}

string Combiner::getCombination(const string& _energy, const string& _material, const string& _evil) {
    map<string, string> combinations = {
        {"Cósmica_Orgánico_Astuta", "INTELIGENCIA"},
        {"Elemental_Radioactivo_Caótica", "DESTRUCCION"},
        {"Oscura_Orgánico_Despiadada", "REGENERACION"},
        {"Elemental_Metélico_Despiadada", "FUERZA"},
        {"Oscura_Metélico_Astuta", "MALDAD"},
        {"Oscura_Radioactivo_Despiadada", "VENENO"},
        {"Cósmica_Radioactivo_Caótica", "LOCURA"},
        {"Cósmica_Metélico_Astuta", "TECNOLOGIA"},
        {"Elemental_Orgánico_Caótica", "VELOCIDAD"}
    };

    string combination = _energy + "_" + _material + "_" + _evil;

    if (combinations.find(combination) != combinations.end()) {
        return combinations[combination];
    } else {
        return "BUENO";
    }
}

Monster* Combiner::combine() {
    if (material->length == 0 || energy->length == 0 || evil->length == 0)
        return nullptr;

    bool temp = true;
    string combinationResult = getCombination(energy->peek(), material->peek(), evil->peek());



    if (combinationResult == "BUENO")
        temp = false;


    Monster* newMonster = new Monster(combinationResult, energy->peek() + ", " + material->peek() + ", " + evil->peek(), temp);


    if (temp) {



        if (toBaking->length < toBaking->capacity){
            toBaking->enqueue(newMonster);
            writeToQueueLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(newMonster->tostring()) + " was enqueued.");
            writeToGeneralLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(newMonster->tostring()) + " was enqueued.");
        }
    } else {
        garbage->insert(newMonster);
        writeToGarbageCollectorLog("[" + getTimestamp() + "] The monster " + QString::fromStdString(newMonster->tostring()) + " entered because it was GOOD.");
        writeToGeneralLog("[" + getTimestamp() + "] The monster " + QString::fromStdString(newMonster->tostring()) + " entered the garbage collector because it was GOOD.");
    }


    evil->dequeue();
    energy->dequeue();
    material->dequeue();

    qDebug() << QString::fromStdString(combinationResult);

    return newMonster;
}
