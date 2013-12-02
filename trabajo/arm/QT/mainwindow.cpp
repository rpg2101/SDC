#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "funsock.h"
#include <stdio.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( ui->pushButton,   SIGNAL( released() ), this, SLOT( conectarsock()) ) ;
    connect( ui->pushButton_2, SIGNAL( released() ), this, SLOT( cerrarsock() ) );
    connect( ui->pushButton_3, SIGNAL( released() ), this, SLOT( recibirsock()) );

}

void MainWindow::conectarsock()
{
    socktcp = conectar("localhost",3550);

    //socktcp = conectar("192.168.1.2",3550);
    if (socktcp!=-1){
        ui->label_3->setText("Conectado");

    }
}

void MainWindow::recibirsock()
{
    while(1){
    recibir (socktcp,datos);
    ui->label_2->setText(datos) ;
    printf("salida recibir\n");
    enviar(socktcp,"ACK\0");
    printf("salida enviar\n");
    //sleep(1);
    ui->label_2->repaint();
    ui->label_2->update();
    }
}

void MainWindow::cerrarsock()
{
    enviar(socktcp,"END\0");
    cerrar (socktcp);
    ui->label_3->setText("Desconectado");
}

MainWindow::~MainWindow()
{
    delete ui;
}
