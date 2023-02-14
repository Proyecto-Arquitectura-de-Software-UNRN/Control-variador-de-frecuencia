#ifndef SYS_H
#define SYS_H

#include <QMainWindow>
#include "invoker.h"
#include"vdf.h"
#include"command.h"
#include<iostream>
#include<stdlib.h>
#include <math.h>

#define LENTA 1
#define INTERMEDIA 2
#define RAPIDA 3

#define ACELERAR 0
#define DESACELERAR 1
#define PARAR 2
#define ACTUALIZAR 3

#define REPOSO 1
#define ACELERANDO 2
#define DESACELERANDO 3
#define REGIMEN 4
#define PARANDO 5

QT_BEGIN_NAMESPACE
namespace Ui { class SYS; }
QT_END_NAMESPACE

class SYS : public QMainWindow
{
    Q_OBJECT

public:
    SYS(QWidget *parent = nullptr);
    ~SYS();
    bool obtener_parametros();

private slots:
    void on_ONBOT_clicked();

    void on_OFFBOT_clicked();

    void on_ACTBOT_clicked();

    void receive_vel(int value);
    void cambio_estado_reposo();
    void cambio_estado_regimen();

private:
    int vreg, tesp, esc, pen; // Parametros para funcion actualizar
    int estado; // estado del sistema
    Vdf& variador = Vdf::getInstance(); // Unica instancia en todo el programa
    Invoker invocador=Invoker(&vreg, &tesp, &esc, &pen);
    Ui::SYS *ui;
};
#endif // SYS_H
