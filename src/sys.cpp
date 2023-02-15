#include "sys.h"
#include "ui_sys.h"
#include<iostream>
#include<stdlib.h>
#include <ctime>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <windows.h>
#include "dialog.h"
#include "dialog2.h"

SYS::SYS(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SYS)
{
    ui->setupUi(this);

    this->estado = REPOSO;
    ui->textEdit->append("Motor APAGADO");
    ui->textEdit->append("ESTADO:Reposo");

    connect(&variador,SIGNAL(transmit_vel(int)),this,SLOT(receive_vel(int)));
    connect(&variador,SIGNAL(transmit_estado_reposo()),this,SLOT(cambio_estado_reposo()));
    connect(&variador,SIGNAL(transmit_estado_regimen()),this,SLOT(cambio_estado_regimen()));
}

SYS::~SYS()
{
    delete ui;
}

//****************************************************************

void SYS::on_ONBOT_clicked() //Marcha
{
    switch(estado){
        case REPOSO:
            if(variador.getVelreg() > 0){
                estado = ACELERANDO;
                ui->textEdit->clear();
                ui->textEdit->append("Motor ENCENDIDO");
                ui->textEdit->append("ESTADO: Acelerando");
                CAcelerar *acelerarMotor = new CAcelerar;
                Invoker *boton_accion_apretado = new Invoker(acelerarMotor);
                boton_accion_apretado->Funcion();
            }
            break;

        case REGIMEN:
            if(variador.getVelreg() < variador.getVel()){
                estado = DESACELERANDO;
                ui->textEdit->clear();
                ui->textEdit->append("Motor ENCENDIDO");
                ui->textEdit->append("ESTADO: Desacelerando");
                CDesacelerar *desacelerarMotor = new CDesacelerar;
                Invoker *boton_accion_apretado = new Invoker(desacelerarMotor);
                boton_accion_apretado->Funcion();
            }
            if(variador.getVelreg() > variador.getVel() ){
                estado = ACELERANDO;
                ui->textEdit->clear();
                ui->textEdit->append("Motor ENCENDIDO");
                ui->textEdit->append("ESTADO: Acelerando");
                CAcelerar *acelerarMotor = new CAcelerar;
                Invoker *boton_accion_apretado = new Invoker(acelerarMotor);
                boton_accion_apretado->Funcion();
            }
            break;

        case ACELERANDO:
            estado = ACELERANDO;
            break;

        case DESACELERANDO:
            estado = DESACELERANDO;
            break;

        case PARANDO:
            estado = PARANDO;
            break;

        default:
            estado = REPOSO;
            break;
    }
}

void SYS::on_OFFBOT_clicked() //Parada de emergencia
{
    switch(estado){
        case PARANDO:
            estado = PARANDO;
            break;

        case REPOSO:
            estado = REPOSO;
            break;

        default:
            estado = PARANDO;
            ui->textEdit->clear();
            ui->textEdit->append("Motor ENCENDIDO");
            ui->textEdit->append("ESTADO: Parando");
            CApagar *apagarMotor = new CApagar;
            Invoker *boton_parada_apretado = new Invoker(apagarMotor);
            boton_parada_apretado->Funcion();
    }
}

void SYS::on_ACTBOT_clicked() //Actualizar parametros VDF
{
    int* params = this->obtener_parametros();
    if(params[0] == -1){
        Dialog2 params_err;
        params_err.setModal(true);
        params_err.exec();
        return;
    }
    CActualizarParametros* actualizarVdf = new CActualizarParametros(params[0],params[1],params[2],params[3]);
    Invoker* boton_actualizar_apretado = new Invoker(actualizarVdf);
    boton_actualizar_apretado->Funcion();
    Dialog act_params;
    act_params.setModal(true);
    act_params.exec();
}

void SYS::receive_vel(int value)
{
    ui->lcdNumber->display(value);
}

void SYS::cambio_estado_regimen(){
    estado = REGIMEN;
    ui->textEdit->clear();
    ui->textEdit->append("Motor ENCENDIDO");
    ui->textEdit->append("ESTADO: REGIMEN");
}

void SYS::cambio_estado_reposo(){
    estado = REPOSO;
    ui->textEdit->clear();
    ui->textEdit->append("Motor APAGADO");
    ui->textEdit->append("ESTADO: REPOSO");
}

int* SYS::obtener_parametros(){

    static int parametros[4];

    if(ui->lineEdit->text() == ""){
        parametros[0] = -1;
        return parametros;
    }
    if(ui->lineEdit_2->text() == ""){
        parametros[0] = -1;
        return parametros;
    }
    if(ui->lineEdit_3->text() == "" || ui->lineEdit_3->text().toInt()>sqrt(pow(variador.getVel()-ui->lineEdit->text().toInt(),2))){
        parametros[0] = -1;
        return parametros;
    }
    if (!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked() && !ui->radioButton_3->isChecked()){
        parametros[0] = -1;
        return parametros;
    }

    parametros[0]=ui->lineEdit->text().toInt();
    parametros[1]=ui->lineEdit_2->text().toInt();
    parametros[2]=ui->lineEdit_3->text().toInt();

    if(ui->radioButton->isChecked())//boton de opciones
        parametros[3] = LENTA;
    else if(ui->radioButton_2->isChecked())
        parametros[3] = INTERMEDIA;
    else if(ui->radioButton_3->isChecked())
        parametros[3] = RAPIDA;

    return (parametros);
}
