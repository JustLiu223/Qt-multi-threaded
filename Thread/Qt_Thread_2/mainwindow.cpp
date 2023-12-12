#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include<QThread>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建不同的任务对象
    Generate *gen = new Generate;
    BubbleSort *bubble = new BubbleSort;
    QuickSort *quick = new QuickSort;
    //创建线程
    QThread *t1 = new QThread;
    QThread *t2 = new QThread;
    QThread *t3 = new QThread;
    //将任务移动到指定的函数
    gen->moveToThread(t1);
    bubble->moveToThread(t2);
    quick->moveToThread(t3);
    //信号槽关联
    connect(this,&MainWindow::starting,gen,&Generate::working);
    connect(gen,&Generate::sendArray,bubble,&BubbleSort::working);
    connect(gen,&Generate::sendArray,quick,&QuickSort::working);
    connect(ui->start,&QPushButton::clicked,this,[=](){
        emit starting(10000);
        t1->start();  //线程启动
    });
    connect(gen,&Generate::sendArray,this,[=](QVector<int>list){

        t2->start();
        t3->start();
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
    connect(this,&MainWindow::destroy,this,[=](){
        t1->quit();
        t1->wait();
        t1->deleteLater();
        t2->quit();
        t2->wait();
        t2->deleteLater();
        t3->quit();
        t3->wait();
        t3->deleteLater();
        gen->deleteLater();
        bubble->deleteLater();
        quick->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
