#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建线程对象
    Generate *gen = new Generate;
    BubbleSort *bubble = new BubbleSort;
    QuickSort *quick = new QuickSort;
    connect(this,&MainWindow::starting,gen,&Generate::recvNum);
    connect(ui->start,&QPushButton::clicked,this,[=](){
        emit starting(10000);
        gen->start();
    });
    connect(gen,&Generate::sendArray,this,[=](QVector<int>list){
        bubble->start();
        quick->start();
        quick->recvNum(list);
        bubble->recvNum(list);
        for(int i=0;i<list.size();i++){
            ui->randList->addItem(QString::number(list.at(i)));
        }
    });
    //主线程显示冒泡排序
    connect(bubble,&BubbleSort::sendArray,this,[=](QVector<int>list){
        for(int i=0;i<list.size();i++){
            ui->bubbleList->addItem(QString::number(list.at(i)));
        }
    });
    connect(quick,&QuickSort::sendArray,this,[=](QVector<int>list){
        for(int i=0;i<list.size();i++){
            ui->quickList->addItem(QString::number(list.at(i)));
        }
    });
    //释放资源
    connect(this,&MainWindow::destroyed,this,[=](){
        gen->quit();
        gen->deleteLater();
        bubble->quit();
        bubble->deleteLater();
        quick->quit();
        quick->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
