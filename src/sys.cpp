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
                invocador.Funcion(ACELERAR);
            }
            break;

        case REGIMEN:
            if(variador.getVelreg() < variador.getVel()){
                estado = DESACELERANDO;
                ui->textEdit->clear();
                ui->textEdit->append("Motor ENCENDIDO");
                ui->textEdit->append("ESTADO: Desacelerando");
                invocador.Funcion(DESACELERAR);
            }
            if(variador.getVelreg() > variador.getVel() ){
                estado = ACELERANDO;
                ui->textEdit->clear();
                ui->textEdit->append("Motor ENCENDIDO");
                ui->textEdit->append("ESTADO: Acelerando");
                invocador.Funcion(ACELERAR);
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
            invocador.Funcion(PARAR);
    }
}

void SYS::on_ACTBOT_clicked() //Actualizar parametros VDF
{
    if(!this->obtener_parametros())
        return;
    invocador.Funcion(ACTUALIZAR);
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

bool SYS::obtener_parametros(){

    if(ui->lineEdit->text() == "")
        return false;
    if(ui->lineEdit_2->text() == "")
        return false;
    if(ui->lineEdit_3->text() == "" || ui->lineEdit_3->text().toInt()>sqrt(pow(variador.getVel()-ui->lineEdit->text().toInt(),2)))
        return false;
    if (!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked() && !ui->radioButton_3->isChecked())
        return false;

    vreg=ui->lineEdit->text().toInt();
    tesp=ui->lineEdit_2->text().toInt();
    esc=ui->lineEdit_3->text().toInt();

    if(ui->radioButton->isChecked())//boton de opciones
        pen = LENTA;
    else if(ui->radioButton_2->isChecked())
        pen = INTERMEDIA;
    else if(ui->radioButton_3->isChecked())
        pen = RAPIDA;

    return true;
}
