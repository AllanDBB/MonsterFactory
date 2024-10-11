#include "../../queues.h"
#include <QDebug>
MaterialQueue::MaterialQueue(int _capacity) {
    front = nullptr;
    rear = nullptr;
    length = 0;
    capacity = _capacity;
}

void MaterialQueue::enqueue(string value) {
    if (length >= capacity){
        qDebug() << "Capacidad máxima alcanzada.";
        return;
    }
    MaterialNode* newNode = new MaterialNode();

    newNode->data = value;
    newNode->next = nullptr;

    if (rear == nullptr) {
        front = rear = newNode;
        return;
    }

    rear->next = newNode;
    rear = newNode;
    length++;
}

string MaterialQueue::dequeue() {
    if (isEmpty()) {
        return "";
    }

    MaterialNode* temp = front;
    string value = front->data;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }
    length--;
    return value;
}

bool MaterialQueue::isEmpty() {
    return length == 0;
}

string MaterialQueue::peek() {
    if (isEmpty()) {
        return "";
    }
    return front->data;
}

MonsterQueue::MonsterQueue(int _capacity) {
    first = nullptr;
    capacity = _capacity;
    length = 0;
}


bool MonsterQueue::isEmpty() {
    return length == 0;
}

void MonsterQueue::enqueue(Monster* monster) {


    if (isEmpty())
        first = new MonsterNode(monster);
    else {
        MonsterNode* temp = first;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        MonsterNode* newMonster = new MonsterNode(monster);
        temp->next = newMonster;
    }

    length ++;
}

Monster* MonsterQueue::dequeue() {
    if (isEmpty())
        return nullptr;
    else {
        MonsterNode* temp = first;
        first = first->next;
        temp->next = nullptr;
        length--;
        return temp->monster;
    }

}

string MonsterQueue::peek() {
    if (isEmpty())
        return "";
    return first->monster->type;
}
