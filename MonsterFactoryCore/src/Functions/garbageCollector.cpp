#include "../../garbageCollector.h"
#include "../../queues.h"

// Constructor
GarbageCollector::GarbageCollector() : first(nullptr), last(nullptr), length(0) {}
// Constructor de MonsterNode
MonsterNode::MonsterNode(Monster* _monster) : monster(_monster), next(nullptr), prev(nullptr) {}
// Método para insertar un monstruo en el recolector de basura
void GarbageCollector::insert(Monster* monster) {
    MonsterNode* newNode = new MonsterNode(monster); // Asegúrate de que MonsterNode esté definido correctamente
    if (last) {
        last->next = newNode; // Conecta el nuevo nodo
    } else {
        first = newNode; // Si es el primer nodo, inicializa primero
    }
    last = newNode; // Actualiza el último nodo
    length++;
}
