#include "vdf.h"
#include<iostream>
#include<stdlib.h>

Vdf::Vdf(){
    this->velocidad = 0;
    this->velocidadregimen = 0;
    this->tiempo_escala = 0;
    this->escalas = 0;
    this->pendiente = 0;
    this->parada_acel = false;
}

int Vdf::getVel(){
    return this->velocidad;
}

void Vdf::setVel(int vel){
    this->velocidad= vel;
}

void Vdf::setVelreg(int velreg){
    this->velocidadregimen= velreg;
}
int Vdf::getVelreg(){
    return this->velocidadregimen;
}

void Vdf::setSeg(int seg){
    this->tiempo_escala= seg;
}
int Vdf::getSeg(){
    return this->tiempo_escala;
}

void Vdf::setEscalas(int Esc){
    this->escalas= Esc;
}
int Vdf::getEscalas(){
    return this->escalas;
}

int Vdf::getPendiente(){
    return this->pendiente;
}
void Vdf::setPendiente(int pend){
    this->pendiente= pend;
}

void Vdf::delay_variador( int tiempo)
{
    QTime dieTime = QTime::currentTime().addMSecs( tiempo);
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

//*********************************************************************************************

void Vdf::ActualizarParametros(int *Vregimen, int *Tesp, int *esc, int *pen){
    this->velocidadregimen= *Vregimen;
    this->tiempo_escala= *Tesp;
    this->escalas= *esc;
    this->pendiente= *pen;
}

void Vdf::aceleracion(){
    if (this->velocidadregimen == 0 || this->velocidad == this->velocidadregimen)
        return;
    int ini = this->velocidad;
    int fin = this->velocidadregimen;
    int resta = fin - ini;
    int rpm=resta/this->escalas; //cada escala
    int delay_pen;

    if(this->pendiente == 1)
        delay_pen = 3000;
    else if(this->pendiente == 2)
        delay_pen = 2000;
    else
        delay_pen = 1000;

    for (int i = ini; i <= fin; i++)
    {
        if (this->parada_acel){
            this->parada_acel = false;
            return;
        }

        this->velocidad=i;
        emit transmit_vel(this->velocidad);

        if (i == this->velocidadregimen)
            break;

        if( (i % rpm == 0)&&(i!=ini)&&(i!=fin-1)){

            this->delay_variador(this->tiempo_escala*1000);
        }
        else{
            this->delay_variador(delay_pen);//delay grande, aceleracion lenta
        }
    }
    emit transmit_estado_regimen();
}

void Vdf::desaceleracion(){
    if (this->velocidad == 0 || this->velocidad == this->velocidadregimen)
        return;
    int ini = this->velocidad;
    int fin = this->velocidadregimen;
    int resta = fin - ini;
    int rpm=resta/this->escalas; //cada escala
    int delay_pen;

    if(this->pendiente == 1)
        delay_pen = 3000;
    else if(this->pendiente == 2)
        delay_pen = 2000;
    else
        delay_pen = 1000;

    for (int i = ini; i >= fin; i--)
    {
        this->velocidad=i;
        emit transmit_vel(this->velocidad);

        if (i == this->velocidadregimen)
            break;

        if( (i % rpm == 0)&&(i!=ini)&&(i!=fin+1)  ){

            this->delay_variador(this->tiempo_escala*1000);
        }
        else{
            this->delay_variador(delay_pen);
        }

    }
    if(this->velocidad == 0)
        emit transmit_estado_reposo();
    else
        emit transmit_estado_regimen();
}

void Vdf::Apagar(){
    if(this->velocidad != this->velocidadregimen)
        this->parada_acel = true;
    int aux_vel_reg = this->velocidadregimen;
    int aux_seg = this->tiempo_escala;
    int aux_pen = this->pendiente;
    int aux_esc = this->escalas;
    this->velocidadregimen = 0;
    this->tiempo_escala = 1;
    this->pendiente = 3;
    this->escalas = 1;
    this->desaceleracion();
    this->velocidadregimen = aux_vel_reg;
    this->tiempo_escala = aux_seg;
    this->pendiente = aux_pen;
    this->escalas = aux_esc;
}
