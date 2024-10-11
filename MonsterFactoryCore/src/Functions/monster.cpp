#include "../../monster.h"
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace std::chrono;

Monster::Monster(string _type, string _combination, bool _quality) {
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

string Monster::tostring() {
    return "Monstruo " + to_string(ID) + " , Tipo: " + type + " , Combinación " + combination;
}
