#include "../../furnace.h"
#include <QDebug>
Furnace::Furnace(int _time, int cap1, int cap2, int cap3, int cap4, MonsterQueue* _toQuality) {
    tray1 = new Tray(cap1);
    tray2 = new Tray(cap2);
    tray3 = new Tray(cap3);
    tray4 = new Tray(cap4);
    toQuality = _toQuality;
    time = _time;
}

bool Furnace::isComplete() {
    return tray1->isComplete() && tray2->isComplete() && tray3->isComplete() && tray4->isComplete();
}

void Furnace::add(Monster* monster) {
    if (isComplete())
        return;

    if (!(tray1->isComplete()) && tray1->inProduction) {

        tray1->add(monster);
        writeToFurnaceLog("[" + getTimestamp() + "] Monster" + QString::fromStdString(monster->tostring()) + " added to tray 1.");
        writeToGeneralLog("[" + getTimestamp() + "] Monster" + QString::fromStdString(monster->tostring()) + " added to tray 1.");
        return;
    }

    if (!(tray2->isComplete()) && tray2->inProduction) {
        tray2->add(monster);
        writeToFurnaceLog("[" + getTimestamp() + "] Monster" + QString::fromStdString(monster->tostring()) + " added to tray 2.");
        writeToGeneralLog("[" + getTimestamp() + "] Monster" + QString::fromStdString(monster->tostring()) + " added to tray 2.");
        return;
    }

    if (!(tray3->isComplete()) && tray3->inProduction) {
        tray3->add(monster);
        writeToFurnaceLog("[" + getTimestamp() + "] Monster" + QString::fromStdString(monster->tostring()) + " added to tray 3.");
        writeToGeneralLog("[" + getTimestamp() + "] Monster" + QString::fromStdString(monster->tostring()) + " added to tray 3.");
        return;
    }

    if (!(tray4->isComplete()) && tray4->inProduction) {
        tray4->add(monster);
        writeToFurnaceLog("[" + getTimestamp() + "] Monster" + QString::fromStdString(monster->tostring()) + " added to tray 4.");
        writeToGeneralLog("[" + getTimestamp() + "] Monster" + QString::fromStdString(monster->tostring()) + " added to tray 4.");
        return;
    }

}

void Furnace::empty() {
    Monster* temp;

    while (tray1->length != 0 && tray1->inProduction) {
        temp = tray1->pop();
        writeToFurnaceLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(temp->tostring()) + " emptied from tray 1.");
        writeToGeneralLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(temp->tostring()) + " emptied from tray 1.");
        toQuality->enqueue(temp);
    }

    while (tray2->length != 0 && tray2->inProduction) {
        temp = tray2->pop();
        writeToFurnaceLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(temp->tostring()) + " emptied from tray 2.");
        writeToGeneralLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(temp->tostring()) + " emptied from tray 2.");
        toQuality->enqueue(temp);
    }

    while (tray3->length != 0 && tray3->inProduction) {
        temp = tray3->pop();
        writeToFurnaceLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(temp->tostring()) + " emptied from tray 3.");
        writeToGeneralLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(temp->tostring()) + " emptied from tray 3.");
        toQuality->enqueue(temp);
    }

    while (tray4->length != 0 && tray4->inProduction) {
        temp = tray4->pop();
        writeToFurnaceLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(temp->tostring()) + " emptied from tray 4.");
        writeToGeneralLog("[" + getTimestamp() + "] Monster " + QString::fromStdString(temp->tostring()) + " emptied from tray 4.");
        toQuality->enqueue(temp);
    }
}

void Furnace::playTray(int tray) {
    switch (tray) {
    case 1: tray1->inProduction = true; break;
    case 2: tray2->inProduction = true; break;
    case 3: tray3->inProduction = true; break;
    case 4: tray4->inProduction = true; break;
    default: return;
    }
}

void Furnace::stopTray(int tray) {
    switch (tray) {
    case 1: tray1->inProduction = false; break;
    case 2: tray2->inProduction = false; break;
    case 3: tray3->inProduction = false; break;
    case 4: tray4->inProduction = false; break;
    default: return;
    }
}
