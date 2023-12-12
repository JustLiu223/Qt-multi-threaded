#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QVector>
#include <QThreadPool>
//生成随机数
class Generate : public QObject, public QRunnable    //多继承，继承QRunnable以重写run函数，继承QObject 以使用信号槽机制
{
    Q_OBJECT
public:
    explicit Generate (QObject *parent = nullptr);
    void run() override;
    void recvNum(int num);                      //接收主线程传来的随机数个数
signals:
    void sendArray(QVector<int> num);                //发送生成的随机数列表
private:
    int m_num;                    //生成随机数个数
};

class BubbleSort : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit BubbleSort (QObject *parent = nullptr);
    void recvNum(QVector<int> num);                             //接收别的线程的随机数列表
    void run() override;                              //重写run函数以进行冒泡排序
signals:
    void sendArray(QVector<int> num);                   //发送排序后的列表
private:
    QVector<int> m_list;
};

class QuickSort : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit QuickSort (QObject *parent = nullptr);
    void recvNum(QVector<int> num);
    void run() override;                                      //重写run函数进行快速排序
signals:
    void sendArray(QVector<int> num);
private:
    QVector<int> m_list;
};

#endif // MYTHREAD_H
