//
// Created by adbyb on 9/29/2024.
//


#include <bits/stdc++.h>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace std::chrono;

#ifndef MONSTER_H
#define MONSTER_H

struct Monster{

    long long ID;
    string combination;
    string type;

    time_t timestampCreation;
    time_t timestampBakingStart;
    time_t timestampBakingEnd;
	time_t timestampDelivered;

	//Tray * tray;

    int inspector;
	bool quality;

	enum State{
		inProduction,
		inStock,
		delivered
	};

	State state;

	Monster(string _type, string _combination, bool _quality){

		type = _type;
		combination = _combination;
		timestampCreation = system_clock::to_time_t(system_clock::now());
		state = inProduction;
		quality = _quality;

        tm *ltm = localtime(&timestampCreation);
        int seconds = ltm->tm_sec;
        int minutes = ltm->tm_min;
        int hours = ltm->tm_hour;
        int day = ltm->tm_mday;
        int month = ltm->tm_mon + 1;
        int year = (ltm->tm_year + 1900) % 100;
        ID = seconds * 10000000000LL + minutes * 100000000LL + hours * 1000000LL +
             day * 10000LL + month * 100LL + year;

	}

	string tostring(){
        return "Monstruo " + to_string(ID) + " , Tipo: " + type + " , Combinación " + combination;
	}

};
#endif //MONSTER_H
