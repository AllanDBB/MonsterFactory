#include <bits/stdc++.h>
#include "garbageCollector.h"

using namespace std;

#ifndef COMBINER_H
#define COMBINER_H

struct Combiner{

	// This combiner works for only 3 queues (material, energy, evil).
	// Change it for more materials.

	MaterialQueue* material;
	MaterialQueue* energy;
	MaterialQueue* evil;
	MonsterQueue* toBaking;
	GarbageCollector* garbage;

	Combiner(MaterialQueue* m, MaterialQueue* e, MaterialQueue* ev, MonsterQueue* _toBaking, GarbageCollector* _garbage){
		material = m;
		energy = e;
		evil = ev;
		toBaking = _toBaking;
		garbage = _garbage;
	}

	string getCombination(const string& _energy, const string& _material, const string& _evil) {

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

	Monster* combine(){
		if (material->isEmpty() || energy->isEmpty() || evil->isEmpty())
			return nullptr;

		bool temp = true;
		string combinationResult = getCombination(energy->peek(), material->peek(), evil->peek());

		if (combinationResult == "BUENO")
			temp = false;

		Monster* newMonster = new Monster(combinationResult, energy->peek() + ", " + material->peek() + ", " + evil->peek(), temp);

		if (temp) {
			toBaking->enqueue(newMonster);
			writeToQueue("["+getTimestamp()+"] Monster "+newMonster->tostring()+" was enqueued.");
			writeToGeneralLog("["+getTimestamp()+"] Monster "+newMonster->tostring()+" was enqueued.");
		}
		else {
			garbage->insert(newMonster);
			writeToGarbageCollectorLog("[" + getTimestamp() + "] The monster " +newMonster->tostring()+" entered because it was GOOD.");
			writeToGeneralLog("[" + getTimestamp() + "] The monster " +newMonster->tostring()+ " entered the garbage collector because it was GOOD.");
		}

		evil->dequeue();
		energy->dequeue();
		material->dequeue();

		return newMonster;
	}

};
#endif //COMBINER_H
