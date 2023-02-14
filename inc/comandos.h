/*
#ifndef COMANDOS_H
#define COMANDOS_H
#include<iostream>
#include<stdlib.h>

#include"interfaz1.h"
#include "motor.h"

class Comandos: public Interfaz1{

    Motor m;
public:
    Comandos(Motor pm_){
        m=pm_;
    }


    void Ejecutar(){
            m.Encender();
        }
};

class ComandoEncender : public Interfaz1{
    Motor m;
public:
    ComandoEncender(Motor pm){
        m=pm;
    }
    void Ejecutar(){
        m.Encender();
    }
};
class ComandoApagar : public Interfaz1{
    Motor m;
public:
    ComandoApagar(Motor pm){
        m=pm;
    }
    void Ejecutar(){
        m.Apagar();
    }
};
class ComandoActualizarParametros : public Interfaz1{
    Motor m;
public:
    ComandoActualizarParametros(Motor pm){
        m=pm;
    }
    void Ejecutar(){
        m.ActualizarParametros();
    }
};



#endif // COMANDOS_H
*/
