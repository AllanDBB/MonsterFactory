#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QMainWindow>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class GameScreen; }
QT_END_NAMESPACE

class Worker : public QObject {
    Q_OBJECT
public:
    Worker() {}
    ~Worker() {}

signals:
    void finished();  // Señal para indicar que la etapa ha terminado

public slots:
    void process(int duration);  // Proceso de la etapa
};

class GameScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr);
    ~GameScreen();

private:
    Ui::GameScreen *ui;

    QThread * threadStage1;
    QThread * threadStage2;
    QThread * threadStage3;
    QThread * threadStage4;
    QThread * threadStage5;
    QThread * threadStage6;

    Worker *workerStage1;
    Worker *workerStage2;
    Worker *workerStage3;
    Worker *workerStage4;
    Worker *workerStage5;
    Worker *workerStage6;

    void startStage1(int);
    void startStage2(int);
    void startStage3(int);
    void startStage4(int);
    void startStage5(int);
    void startStage6(int);

};

#endif // GAMESCREEN_H
