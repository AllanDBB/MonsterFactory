#include "../../sources.h"
#include <QDebug>
Source::Source(int _time, RawMaterials* _materials, MaterialQueue* _queue) {
    time = _time;
    materials = _materials;
    queue = _queue;
}

void Source::start() {
    inProduction = true;
}

void Source::stop() {
    inProduction = false;
}

void Source::produce() {
    if (!inProduction) return;

    int materialIndex = rand() % materials->length;
    Material* producedMaterial = materials->returnFromIndex(materialIndex);
    string token = to_string(producedMaterial->index) + " " + producedMaterial->name + " " + materials->className;
    queue->enqueue(producedMaterial->name);
}

void Source::changeTime(int _time) {
    time = _time;
}
