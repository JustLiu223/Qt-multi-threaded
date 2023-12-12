#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include<QThreadPool>
MainWindow::MainWindow(QWidget *parent)        //主线程初始化函数
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建不同的任务类
    Generate *gen = new Generate;
    BubbleSort *bubble = new BubbleSort;
    QuickSort *quick = new QuickSort;
    //关联信号槽动作
    connect(this,&MainWindow::starting,gen,&Generate::recvNum);
    connect(gen,&Generate::sendArray,bubble,&BubbleSort::recvNum);
    connect(gen,&Generate::sendArray,quick,&QuickSort::recvNum);
    //开始按钮按下时
    connect(ui->start,&QPushButton::clicked,this,[=](){
        emit starting(10000);
        QThreadPool::globalInstance()->start(gen);
    });
    //显示随机数列表
    connect(gen,&Generate::sendArray,this,[=](QVector<int>list){

        QThreadPool::globalInstance()->start(bubble);
        QThreadPool::globalInstance()->start(quick);
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
    //主线程显示快速排序
    connect(quick,&QuickSort::sendArray,this,[=](QVector<int>list){
        for(int i=0;i<list.size();i++){
            ui->quickList->addItem(QString::number(list.at(i)));
        }
    });

    //释放资源
    connect(this,&MainWindow::destroy,this,[=](){
        gen->deleteLater();
        bubble->deleteLater();
        quick->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
