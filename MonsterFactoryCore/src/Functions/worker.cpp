#include "gamescreen.h"
#include <QThread>

void Worker::process(int duration) {
    QThread::sleep(duration / 1000);
    emit finished();
}
