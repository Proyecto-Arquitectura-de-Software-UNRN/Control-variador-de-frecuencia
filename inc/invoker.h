#ifndef INVOKER_H
#define INVOKER_H
#include<iostream>
#include<stdlib.h>
#include"command.h"
#include "vdf.h"

class Invoker
{
private:
    Command* comando;
public:
    Invoker(Command* nuevoComando);
    void Funcion();
};

#endif // INVOKER_H
