//
// Created by adbyb on 9/29/2024.
//


#include <bits/stdc++.h>

using namespace std;

#ifndef MATERIAL_H
#define MATERIAL_H

struct Material{

    int type;
    int index;
    string name;
    string description;
    Material* next;

    Material(int _type, string _name, string _description, int _index){

        type = _type;
        name = _name;
        description = _description;
        next = nullptr;
        index = _index;
    }
};

struct RawMaterials{
    // Array list of Materials || Assigned by type.

    // Array list technicals:
    Material* firstMaterial;
    int length;

    // Array list settings:
    int type;
    string className;

    RawMaterials(int _type, string _className){
        type = _type;
        className = _className;
        firstMaterial = nullptr;
        length = 0;

    }

    bool addMaterial(int _type, string _name, string _description){

        // Add a material

        // Check if type matches.
        if (type != _type)
           return false;

        if (length == 0){
            Material * newMaterial = new Material(_type, _name, _description, 0);
            firstMaterial = newMaterial;
            length++;
            return true;
        }

        // Check if that name already exists.
        Material* temp = firstMaterial;
        for (int i = 0; i < length; i++){

            if (temp->name == _name)
                return false;

            if (i == length-1)
                break;

            temp = temp->next;
        }

        // Create a new material.
        Material * newMaterial = new Material(_type, _name, _description, length);
        temp->next = newMaterial;
        length++;
        return true;
    }

    Material* returnFromIndex(int _index){

        // Returns a specific material from an index from 0 to length - 1.

        if (_index < 0)
            return nullptr;

        Material* temp = firstMaterial;
        for (int i=0; i<_index; i++){
            temp = temp->next;
        }

        return temp;
    }
};


#endif //MATERIAL_H
