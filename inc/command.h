#ifndef COMMAND_H
#define COMMAND_H
#include<iostream>
#include<stdlib.h>
#include "vdf.h"

class Command
{
public:
    virtual void Ejecutar(){

    }
};

//comandos*****************

class CAcelerar: public Command{

private:
    Vdf& var = var.getInstance();

public:

    void Ejecutar(){
        this->var.aceleracion();
    }
};

//****************************************

class CDesacelerar: public Command{

private:

    Vdf& var = var.getInstance();

public:

    void Ejecutar(){
        this->var.desaceleracion();
    }
};

//****************************************

class CApagar: public Command{

private:

    Vdf& var = var.getInstance();

public:

    void Ejecutar(){
        this->var.Apagar();
    }
};

//****************************************

class CActualizarParametros: public Command{

private:

    Vdf& var = var.getInstance();
    int *vr, *te, *e, *p;

public:

    CActualizarParametros(int *Vreg, int *Tesp, int *esc, int *pen){
        this->vr= Vreg;
        this->te= Tesp;
        this->e= esc;
        this->p = pen;
    }

    void Ejecutar(){
        this->var.ActualizarParametros(vr,te,e,p);
    }
};
//****************************************

#endif // COMMAND_H
