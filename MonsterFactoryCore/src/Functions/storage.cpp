#include "../../storage.h"



void Storage::insert(Monster* monster) {
    MonsterNode* temp = new MonsterNode(monster);
    temp->monster->state = Monster::inStock;
    if (first == nullptr) {
        first = temp;
    } else {
        temp->next = first;
        first = temp;
    }
    length++;
}

MonsterNode* Storage::findMonster(string monsterType) {
    MonsterNode* temp = first;
    while (temp != nullptr) {
        if (temp->monster->type == monsterType && temp->monster->state == Monster::inStock) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
