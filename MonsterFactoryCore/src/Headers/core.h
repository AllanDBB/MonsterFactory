#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>

// Estructura para los materiales
struct RawMaterials {
    int id;
    std::string name;
};

// Estructura para las colas de materiales
struct MaterialQueue {
    void (*enqueue)(const std::string& item);
    std::string (*dequeue)();
    bool (*isEmpty)();
    bool (*isFull)();
};

// Estructura para las colas de monstruos
struct MonsterQueue {
    void (*enqueue)(const std::string& item);
    std::string (*dequeue)();
    bool (*isEmpty)();
    bool (*isFull)();
    std::string (*peek)();
};

// Estructura para las colas de clientes
struct ClientQueue {
    void (*enqueue)(const std::string& item);
    std::string (*dequeue)();
    bool (*isEmpty)();
};

// Estructura para las fuentes
struct Source {
    int time;
    RawMaterials* material;
    MaterialQueue* queue;

    void (*produce)();
    void (*stop)();
    void (*start)();
};

// Estructura para el recolector de basura
struct GarbageCollector {
    void (*collect)();
};

// Estructura para el combinador
struct Combiner {
    int time;

    void (*combine)();
};

// Estructura para el horno
struct Furnace {
    int time;

    void (*add)(const std::string& monster);
    void (*playTray)(int tray);
    void (*stopTray)(int tray);
    void (*empty)();
    bool (*isComplete)();
};

// Estructura para el almacenamiento
struct Storage {
    void (*store)();
};

// Estructura para la calidad
struct Quality {
    int time;
    Storage* storage;
    GarbageCollector* garbageCollector;
    MonsterQueue* queueToQuality;

    void (*activate)();
};

// Estructura para la entrega
struct Delivery {
    Storage* storage;
    ClientQueue* normalClientQueue;
    ClientQueue* priorityClientQueue;

    void (*activate)();
};

// Funciones de inicialización y manipulación
bool init();
int getSourceTime(int source);
void setSourceTime(int source, int time);
void pauseSource();
void resumeSources();
void produceSources();
int getCombineTime();
void setCombineTime(int time);
void combineMonster();
int getTimeFurnace();
void setTimeFurnace(int time);
void addMonsterToFurnace();
void playSpecificTray(int tray);
void stopSpecificTray(int tray);
void emptyFurnace();
bool isFurnaceComplete();
int getInspector1Time();
void setInspector1Time(int time);
int getInspector2Time();
void setInspector2Time(int time);
void activateQuality();
void activateDelivery();
int ping();

#endif // SIMULATION_H
