#ifndef VDF_H
#define VDF_H
#include<iostream>
#include<stdlib.h>
#include "ui_sys.h"
#include <ctime>
#include <QTime>
#include <QTimer>
#include <QObject>

class Vdf : public QObject
{
Q_OBJECT

private:
    int velocidad; //velocidad actual
    int velocidadregimen; //velocidad objetivo
    int tiempo_escala; //tiempo de espera entre escalas
    int escalas;
    int pendiente;
    bool parada_acel;
    Vdf();

signals:
    void transmit_vel(int value);
    void transmit_estado_regimen();
    void transmit_estado_reposo();

public:
    Vdf(Vdf const&) = delete; //constructor de copia
    void operator=(Vdf const&)  = delete; // Sobrecarca del =

    static Vdf& getInstance(){
        static Vdf instance;
        return instance;
    }

    int getVel();
    void setVel(int vel);

    void setVelreg(int velreg);
    int getVelreg();

    void setSeg(int seg);
    int getSeg();

    void setEscalas(int Esc);
    int getEscalas();

    void setPendiente(int pend);
    int getPendiente();

//****************************

    void Apagar();
    void ActualizarParametros(int *Vregimen, int *Tesp, int *esc, int *pen);
    void aceleracion();
    void desaceleracion();
    void delay_variador( int tiempo );
};

#endif // VDF_H
