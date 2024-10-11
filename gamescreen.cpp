#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QThread>
#include <QTimer>
#include <QProgressBar>
#include <QLCDNumber>
#include <QCheckBox>
#include <QSpinBox>
#include <cstdlib>
#include <ctime>

#include "material.h"
#include "sources.h"
#include "queues.h"
#include "garbageCollector.h"
#include "combiner.h"
#include "furnace.h"
#include "quality.h"
#include "storage.h"
#include "delivery.h"
#include "logFunctions.h"

// Global queues.
RawMaterials* material;
RawMaterials* energy;
RawMaterials* evil;
MaterialQueue* materialQueue;
MaterialQueue* energyQueue;
MaterialQueue* evilQueue;

// Sources.
Source* materialSource;
Source* energySource;
Source* evilSource;


// Queue to baking
MonsterQueue* queueToBaking;

//Garbage
GarbageCollector* monsterGarbage;

//Combiner
Combiner* combiner;

// Queue to Quality
MonsterQueue* queueToQuality;

// Furnace
Furnace* furnace;

// Quality
Quality* quality;

// Storage
Storage* storage;

// client queues:
ClientQueue* PriorityClientQueue;
ClientQueue* NormalClientQueue;

// Delivery
Delivery* delivery;


// Initilize gui instances.
QLCDNumber *lcdNumber;
QLCDNumber *lcdNumber2;
QLCDNumber *lcdNumber3;
QLCDNumber *lcdNumber4;
QLCDNumber *lcdNumber5;
QLCDNumber *lcdNumber6;
QLCDNumber *lcdNumber7;
QLCDNumber *lcdNumber8;
QLCDNumber *lcdNumber9;
QLCDNumber *lcdNumber10;

QCheckBox *checkBox;
QCheckBox *checkBox2;
QCheckBox *checkBox3;
QCheckBox *checkBox4;
QCheckBox *checkBox5;
QCheckBox *checkBox6;
QCheckBox *checkBox7;
QCheckBox *checkBox8;

QSpinBox *spinBox;
QSpinBox *spinBox2;
QSpinBox *spinBox3;
QSpinBox *spinBox4;
QSpinBox *spinBox5;
QSpinBox *spinBox6;
QSpinBox *spinBox7;
QSpinBox *spinBox8;
QSpinBox *spinBox9;
QSpinBox *spinBox10;
QSpinBox *spinBox11;
QSpinBox *spinBox12;


int awaitTimeSources = 2000;
int awaitTimeCombiner = 5000;



GameScreen::GameScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameScreen)
    , workerStage1(new Worker())
    , workerStage2(new Worker())
    , workerStage3(new Worker())
    , workerStage4(new Worker())
    , workerStage5(new Worker())
    , workerStage6(new Worker())
{
    ui->setupUi(this);
    srand(time(0));

    // Initialize all components.
    material = new RawMaterials(0, "Material");
    energy = new RawMaterials(1, "Energía");
    evil = new RawMaterials(2, "Maldad");

    material->addMaterial(0, "Orgánico", "..");
    material->addMaterial(0, "Metálico", "..");
    material->addMaterial(0, "Radioactivo", "..");

    energy->addMaterial(1, "Oscura", "..");
    energy->addMaterial(1, "Cósmica", "..");
    energy->addMaterial(1, "Elemental", "..");

    evil->addMaterial(2, "Despiadada", "..");
    evil->addMaterial(2, "Astuta", "..");
    evil->addMaterial(2, "Caótica", "..");

    // Inicialize queues:
    materialQueue = new MaterialQueue(10);
    energyQueue = new MaterialQueue(10);
    evilQueue = new MaterialQueue(10);
    queueToBaking = new MonsterQueue(2);
    queueToQuality = new MonsterQueue(200);

    // Initializing the sources.
    materialSource = new Source(10, material, materialQueue);
    energySource = new Source(10, energy, energyQueue);
    evilSource = new Source(10, evil, evilQueue);

    // Initialize garbage
    monsterGarbage = new GarbageCollector();

    // Initialize combine.
    combiner = new Combiner(materialQueue, energyQueue, evilQueue, queueToBaking, monsterGarbage);

    // Initialize furnace.
    furnace = new Furnace(10, 2, 2, 2, 2, queueToQuality);

    // Initialize storage.
    storage = new Storage();

    // Initialize quality.
    quality = new Quality(storage, monsterGarbage, queueToQuality);

    NormalClientQueue = new ClientQueue();
    PriorityClientQueue = new ClientQueue();
    // Initializing the delivery.
    delivery = new Delivery(storage, NormalClientQueue, PriorityClientQueue);
    readFiles(delivery); // It should be here?

    lcdNumber = findChild<QLCDNumber *>("lcdNumber");
    lcdNumber2 = findChild<QLCDNumber *>("lcdNumber_2");
    lcdNumber3 = findChild<QLCDNumber *>("lcdNumber_3");
    lcdNumber4 = findChild<QLCDNumber *>("lcdNumber_13");
    lcdNumber5 = findChild<QLCDNumber *>("lcdNumber_12");
    lcdNumber6 = findChild<QLCDNumber *>("lcdNumber_6");
    lcdNumber7 = findChild<QLCDNumber *>("lcdNumber_5");
    lcdNumber8 = findChild<QLCDNumber *>("lcdNumber_7");
    lcdNumber9 = findChild<QLCDNumber *>("lcdNumber_4");
    lcdNumber10 = findChild<QLCDNumber *>("lcdNumber_9");

    checkBox = findChild<QCheckBox *>("checkBox_7");
    checkBox2 = findChild<QCheckBox *>("checkBox_8");
    checkBox3 = findChild<QCheckBox *>("checkBox_9");
    checkBox4 = findChild<QCheckBox *>("checkBox");
    checkBox5 = findChild<QCheckBox *>("checkBox_3");
    checkBox6 = findChild<QCheckBox *>("checkBox_2");
    checkBox7 = findChild<QCheckBox *>("checkBox_4");
    checkBox8 = findChild<QCheckBox *>("checkBox_5");

    checkBox4->setChecked(true);
    checkBox5->setChecked(true);
    checkBox6->setChecked(true);
    checkBox7->setChecked(true);
    checkBox8->setChecked(true);

    spinBox = findChild<QSpinBox *>("spinBox_6");
    spinBox2 = findChild<QSpinBox *>("spinBox_7");
    spinBox3 = findChild<QSpinBox *>("spinBox_8");

    spinBox->setValue(10);
    spinBox2->setValue(10);
    spinBox3->setValue(10);

    spinBox4 = findChild<QSpinBox *>("spinBox_9");
    spinBox5 = findChild<QSpinBox *>("spinBox_10");
    spinBox6 = findChild<QSpinBox *>("spinBox_12");


    spinBox4->setValue(2);
    spinBox5->setValue(5);
    spinBox6->setValue(2);

    spinBox7 = findChild<QSpinBox *>("spinBox_2");
    spinBox8 = findChild<QSpinBox *>("spinBox_3");
    spinBox9 = findChild<QSpinBox *>("spinBox_5");
    spinBox10 = findChild<QSpinBox *>("spinBox_4");

    spinBox7->setValue(2);
    spinBox8->setValue(2);
    spinBox9->setValue(2);
    spinBox10->setValue(2);

    spinBox11 = findChild<QSpinBox *>("spinBox_16");
    spinBox12 = findChild<QSpinBox *>("spinBox_15");

    spinBox11->setValue(90);
    spinBox12->setValue(90);

    qDebug() << "Testing";

    startStage1(2000);
    startStage2(5000);
    startStage3(2000);
    startStage4(1000);
    startStage5(1000);
    startStage6(1000);


}

GameScreen::~GameScreen()
{
    if (threadStage1){
        threadStage1->quit();
        threadStage1->wait();
    }
    if (threadStage2){
        threadStage2->quit();
        threadStage2->wait();
    }
    if (threadStage3){
        threadStage3->quit();
        threadStage3->wait();
    }
    if (threadStage4){
        threadStage4->quit();
        threadStage4->wait();
    }
    if (threadStage5){
        threadStage5->quit();
        threadStage5->wait();
    }
    if (threadStage6){
        threadStage6->quit();
        threadStage6->wait();
    }

    delete workerStage1;
    delete workerStage2;
    delete workerStage3;
    delete workerStage4;
    delete workerStage5;
    delete workerStage6;

    delete ui;
}
void GameScreen::startStage1(int awaitTime) {
    Worker *workerStage1 = new Worker();
    threadStage1 = new QThread(this);
    workerStage1->moveToThread(threadStage1);


    connect(threadStage1, &QThread::started, [=]() {
        workerStage1->process(awaitTime);
    });

    connect(workerStage1, &Worker::finished, this, [=]() {

        connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            materialSource->queue->capacity = value;
        });

        connect(spinBox2, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            energySource->queue->capacity = value;
        });

        connect(spinBox3, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            evilSource->queue->capacity = value;
        });

        connect(spinBox4, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            awaitTimeSources = value * 1000;
        });

        if (checkBox && checkBox2 && checkBox3){
            connect(checkBox, &QCheckBox::toggled, this, [](bool checked) {
                if (checked) {
                    evilSource->start();
                } else {
                    evilSource->stop();
                }
            } );

            connect(checkBox2, &QCheckBox::toggled, this, [](bool checked) {
                if (checked) {
                    energySource->start();
                } else {
                    energySource->stop();
                }
            } );

            connect(checkBox3, &QCheckBox::toggled, this, [](bool checked) {
                if (checked) {
                    materialSource->start();
                } else {
                    materialSource->stop();
                }
            } );
        }

        materialSource->produce();
        energySource->produce();
        evilSource->produce();

        if (lcdNumber != nullptr && lcdNumber2 != nullptr && lcdNumber3 != nullptr){
            lcdNumber->display(materialSource->queue->length);
            lcdNumber2->display(energySource->queue->length);
            lcdNumber3->display(evilSource->queue->length);
        }
        threadStage1->quit();
        threadStage1->wait();

        workerStage1->deleteLater();
        threadStage1->deleteLater();

        startStage1(awaitTimeSources);
    });

    threadStage1->start();
}

void GameScreen::startStage2(int awaitTime) {
    Worker *workerStage2 = new Worker();
    threadStage2 = new QThread(this);
    workerStage2->moveToThread(threadStage2);

    connect(threadStage2, &QThread::started, [=]() {
        workerStage2->process(awaitTime);
    });
    connect(workerStage2, &Worker::finished, this, [=]() {


        connect(spinBox5, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            combiner->time = value;
            awaitTimeCombiner = value * 1000;

        });

        connect(spinBox6, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            queueToBaking->capacity = value;
        });



        if (combiner != nullptr){
            combiner->combine();
        }

        lcdNumber4->display(queueToBaking->length);
        lcdNumber5->display(monsterGarbage->length);

        threadStage2->quit();
        threadStage2->wait();

        workerStage2->deleteLater();
        threadStage2->deleteLater();

        startStage2(awaitTimeCombiner);
    });

    threadStage2->start();
}

void GameScreen::startStage3(int awaitTime) {
    Worker *workerStage3 = new Worker();
    threadStage3 = new QThread(this);
    workerStage3->moveToThread(threadStage3);

    connect(threadStage3, &QThread::started, [=]() {
        workerStage3->process(awaitTime);
    });
    connect(workerStage3, &Worker::finished, this, [=]() {

        connect(checkBox4, &QCheckBox::toggled, this, [](bool checked) {
            if (checked) {
                furnace->playTray(1);
            } else {
                furnace->stopTray(1);
            }
        } );

        connect(checkBox5, &QCheckBox::toggled, this, [](bool checked) {
            if (checked) {
                furnace->playTray(2);
            } else {
                furnace->stopTray(2);
            }
        } );

        connect(checkBox6, &QCheckBox::toggled, this, [](bool checked) {
            if (checked) {
                furnace->playTray(3);
            } else {
                furnace->stopTray(3);
            }
        } );

        connect(checkBox7, &QCheckBox::toggled, this, [](bool checked) {
            if (checked) {
                furnace->playTray(4);
            } else {
                furnace->stopTray(4);
            }
        } );

        if (lcdNumber6 && lcdNumber7 && lcdNumber8 && lcdNumber9){
            lcdNumber6->display(furnace->tray1->length);
            lcdNumber7->display(furnace->tray2->length);
            lcdNumber8->display(furnace->tray3->length);
            lcdNumber9->display(furnace->tray4->length);
        }

        connect(spinBox7, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            furnace->tray1->capacity = value;

        });
        connect(spinBox8, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            furnace->tray2->capacity = value;

        });
        connect(spinBox9, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            furnace->tray3->capacity = value;

        });
        connect(spinBox10, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            furnace->tray4->capacity = value;

        });

        if (furnace->isComplete()){
            QThread::sleep(10);
            furnace->empty();
        } else {
            if (queueToBaking->length > 0){
                furnace->add(queueToBaking->dequeue());
            }
        }

        threadStage3->quit();
        threadStage3->wait();

        workerStage3->deleteLater();
        threadStage3->deleteLater();

        startStage3(awaitTime);
    });

    threadStage3->start();
}

void GameScreen::startStage4(int awaitTime) {
    Worker *workerStage4 = new Worker();
    threadStage4 = new QThread(this);
    workerStage4->moveToThread(threadStage4);

    connect(threadStage4, &QThread::started, [=]() {
        workerStage4->process(awaitTime);
    });
    connect(workerStage4, &Worker::finished, this, [=]() {

        connect(checkBox8, &QCheckBox::toggled, this, [](bool checked) {
            if (checked) {
                quality->evaluate(true);
            } else {
                quality->evaluate(false);
            }
        } );

        connect(spinBox11, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            quality->inspector1->probability = value;
        });


        connect(spinBox12, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value) {
            quality->inspector2->probability = value;
        });

        if (queueToQuality->length > 0)
            quality->activate();

        threadStage4->quit();
        threadStage4->wait();

        workerStage4->deleteLater();
        threadStage4->deleteLater();

        startStage4(awaitTime);
    });

    threadStage4->start();
}

void GameScreen::startStage5(int awaitTime) {
    Worker *workerStage5 = new Worker();
    threadStage5 = new QThread(this);
    workerStage5->moveToThread(threadStage5);

    connect(threadStage5, &QThread::started, [=]() {
        workerStage5->process(awaitTime);
    });
    connect(workerStage5, &Worker::finished, this, [=]() {

        lcdNumber10->display(storage->length);

        threadStage5->quit();
        threadStage5->wait();
        workerStage5->deleteLater();
        threadStage5->deleteLater();
        startStage5(awaitTime);
    });

    threadStage5->start();
}

void GameScreen::startStage6(int awaitTime) {
    Worker *workerStage6 = new Worker();
    threadStage6 = new QThread(this);
    workerStage6->moveToThread(threadStage6);

    connect(threadStage6, &QThread::started, [=]() {
        workerStage6->process(awaitTime);
    });
    connect(workerStage6, &Worker::finished, this, [=]() {



        if ((NormalClientQueue->length !=0 || PriorityClientQueue->length != 0) && storage->length != 0){
            QThread::sleep(1);
            delivery->activate();
        }

        threadStage6->quit();
        threadStage6->wait();
        workerStage6->deleteLater();
        threadStage6->deleteLater();
        startStage6(awaitTime);
    });

    threadStage6->start();
}
