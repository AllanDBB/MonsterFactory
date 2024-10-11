#include "../../material.h"

// Constructor de Material
Material::Material(int _type, string _name, string _description, int _index)
    : type(_type), name(_name), description(_description), index(_index), next(nullptr) {}

RawMaterials::RawMaterials(int _type, string _className) {
    type = _type;
    className = _className;
    firstMaterial = nullptr;
    length = 0;
}

bool RawMaterials::addMaterial(int _type, string _name, string _description) {
    if (type != _type)
        return false;

    if (length == 0) {
        Material* newMaterial = new Material(_type, _name, _description, 0);
        firstMaterial = newMaterial;
        length++;
        return true;
    }

    Material* temp = firstMaterial;
    for (int i = 0; i < length; i++) {
        if (temp->name == _name)
            return false;

        if (i == length - 1)
            break;

        temp = temp->next;
    }

    Material* newMaterial = new Material(_type, _name, _description, length);
    temp->next = newMaterial;
    length++;
    return true;
}

Material* RawMaterials::returnFromIndex(int _index) {
    if (_index < 0 || _index >= length)
        return nullptr;

    Material* temp = firstMaterial;
    for (int i = 0; i < _index; i++) {
        temp = temp->next;
    }

    return temp;
}
