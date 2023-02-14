#ifndef INVOKER_H
#define INVOKER_H
#include<iostream>
#include<stdlib.h>

#include"command.h"
#include "vdf.h"

class Invoker
{
private:
    Command *comandos[4];
public:
    Invoker(int *vreg, int *tesp, int *esc, int *pen);
    void Funcion(int fun);
};

#endif // INVOKER_H
