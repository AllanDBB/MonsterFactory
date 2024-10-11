#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <string>

using namespace std;

struct Material {
    int type;
    int index;
    string name;
    string description;
    Material* next;

    // Constructor
    Material(int _type, string _name, string _description, int _index);
};

struct RawMaterials {
    Material* firstMaterial;
    int length;
    int type;
    string className;

    // Constructor
    RawMaterials(int _type, string _className);

    // Métodos
    bool addMaterial(int _type, string _name, string _description);
    Material* returnFromIndex(int _index);
};

#endif // MATERIAL_H
