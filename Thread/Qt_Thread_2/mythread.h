#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QVector>
//生成随机数
class Generate : public QObject
{
    Q_OBJECT
public:
    explicit Generate (QObject *parent = nullptr);
    void working(int num);
    // void recvNum(int num);
protected:

signals:
    void sendArray(QVector<int> num);
private:

};

class BubbleSort : public QObject
{
    Q_OBJECT
public:
    explicit BubbleSort (QObject *parent = nullptr);
    void recvNum(QVector<int> num);

    void working(QVector<int> num);
signals:
    void sendArray(QVector<int> num);
private:

};

class QuickSort : public QObject
{
    Q_OBJECT
public:
    explicit QuickSort (QObject *parent = nullptr);
    // void recvNum(QVector<int> num);
    void working(QVector<int> num);
signals:
    void sendArray(QVector<int> num);
private:

};

#endif // MYTHREAD_H
