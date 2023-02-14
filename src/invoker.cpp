#include "invoker.h"
#include "comandos.h"
#include "command.h"
#include<iostream>
#include<stdlib.h>

Invoker::Invoker(int *vreg, int *tesp, int *esc, int *pen){
   comandos[0]= new CAcelerar();
   comandos[1]= new CDesacelerar();
   comandos[2]= new CApagar();
   comandos[3]= new CActualizarParametros(vreg, tesp, esc, pen);
}

void Invoker::Funcion(int fun){
    comandos[fun]->Ejecutar();
}

