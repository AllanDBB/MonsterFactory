#ifndef LOGFUNCTIONS_H
#define LOGFUNCTIONS_H

#include <QString>
#include "delivery.h"


struct Delivery;

void writeToLog(const QString& filePath, const QString& message);
void writeToOrderLog(const QString& message);
void writeToStorageLog(const QString& message);
void writeToInspector1Log(const QString& message);
void writeToInspector2Log(const QString& message);
void writeToGeneralLog(const QString& message);
void writeToGarbageCollectorLog(const QString& message);
void writeToDeliveryLog(const QString& message);
void writeToQueueLog(const QString& message);
void writeToFurnaceLog(const QString& message);
void readFiles(Delivery* requests);
QString getTimestamp();
#endif // LOGFUNCTIONS_H
