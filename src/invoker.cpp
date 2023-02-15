#include "invoker.h"
#include "command.h"
#include<iostream>
#include<stdlib.h>

Invoker::Invoker(Command* nuevoComando){
    this->comando = nuevoComando;
}

void Invoker::Funcion(){
    comando->Ejecutar();
}


