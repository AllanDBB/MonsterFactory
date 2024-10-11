
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <QDir>



#include "../../logFunctions.h"
#include "../../delivery.h"

#include <QDebug>
void readFiles(Delivery *requests) {
    QString folder = "../../MonsterFactoryCore/orders/"; // Usamos QString para las rutas de Qt
    QDir dir(folder); // Crea un objeto QDir para el directorio especificado

    if (!dir.exists()) {

        return;
    }


    // Itera sobre los archivos en el directorio
    for (const QString &fileName : dir.entryList(QDir::Files)) {
        QString path = dir.filePath(fileName); // Obtiene la ruta completa del archivo
        QFile file(path); // Crea un objeto QFile para abrir el archivo

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            continue; // Salta al siguiente archivo
        }

        QTextStream in(&file); // Crea un QTextStream para leer el contenido del archivo
        QString line;
        QString write = "[" + getTimestamp() + "] The order: ";
        QString name = "";


        if (!in.atEnd()) {
            in >> name; // Lee el primer elemento como nombre
            write += "Name: " + name + ", ";
        }

        bool priority = false;
        if (!in.atEnd()) {
            in >> line; // Lee la siguiente línea
            write += "Priority: ";
            if (line == "1STPROGRA") {
                priority = true;
                write += "Yes, ";
            } else {
                write += "No, ";
            }
        }

        QString number = "";
        if (!in.atEnd()) {
            in >> number; // Lee el número
            write += "Number: " + number + ", ";
        }

        write += "of ";

        while (!in.atEnd()) {
            QString monsterName;
            in >> monsterName; // Lee el nombre del monstruo
            if (monsterName.isEmpty()) {
                break; // Rompe si la línea está vacía
            }

            Client *client = new Client(name.toStdString(), priority, number.toStdString());
            StrNode *monster = new StrNode(monsterName.toStdString());
            client->insert(monster);
            write += QString::fromStdString(monster->name) + ", ";

            if (priority) {
                requests->PriorityClientQueue->enqueue(client);
            } else {
                requests->NormalClientQueue->enqueue(client);
            }
        }

        writeToGeneralLog(write);
        writeToOrderLog(write);

        file.close(); // Cierra el archivo
    }
}


void writeToLog(const QString& filePath, const QString& message) {
    QFile logFile(filePath);
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << message << Qt::endl;
        logFile.close();
    } else {
        qDebug() << "No se pudo abrir el archivo de log:" << filePath;
    }
}

QString getTimestamp() {
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}

void writeToOrderLog(const QString& message) {
    writeToLog("../../MonsterFactoryCore/logs/BitacoraPedidos.txt", getTimestamp() + " - " + message);
}

void writeToStorageLog(const QString& message) {
    writeToLog("../../MonsterFactoryCore/logs/BitacoraAlmacen.txt", getTimestamp() + " - " + message);
}

void writeToInspector1Log(const QString& message) {
    writeToLog("../../MonsterFactoryCore/logs/BitacoraInspector1.txt", getTimestamp() + " - " + message);
}

void writeToInspector2Log(const QString& message) {
    writeToLog("../../MonsterFactoryCore/logs/BitacoraInspector2.txt", getTimestamp() + " - " + message);
}

void writeToGeneralLog(const QString& message) {
    writeToLog("../../MonsterFactoryCore/logs/BitacoraGeneral.txt", getTimestamp() + " - " + message);
}

void writeToGarbageCollectorLog(const QString& message) {
    writeToLog("../../MonsterFactoryCore/logs/BitacoraBasurero.txt", getTimestamp() + " - " + message);
}

void writeToDeliveryLog(const QString& message) {
    writeToLog("../../MonsterFactoryCore/logs/BitacoraEntrega.txt", getTimestamp() + " - " + message);
}

void writeToQueueLog(const QString& message) {
    writeToLog("../../MonsterFactoryCore/logs/BitacoraCola.txt", getTimestamp() + " - " + message);
}

void writeToFurnaceLog(const QString& message) {
    writeToLog("../../MonsterFactoryCore/logs/BitacoraHorno.txt", getTimestamp() + " - " + message);
}
