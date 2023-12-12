#include "mythread.h"
#include<QElapsedTimer>
#include<QDebug>
Generate::Generate(QObject *parent)
    : QObject{parent}
{}
BubbleSort::BubbleSort(QObject *parent)
    : QObject{parent}
{}
QuickSort::QuickSort(QObject *parent)
    : QObject{parent}
{}


int partition(QVector<int> &arr, int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为基准

    int i = low - 1; // 初始化较小元素的索引

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            qSwap(arr[i], arr[j]);
        }
    }

    qSwap(arr[i + 1], arr[high]);
    return i + 1;
}

// void quickSort(QVector<int> &arr, int low, int high) {

// }
void QuickSort::working(QVector<int>list)
{
    int low =0;
    int high =list.size()-1;
    qDebug()<<"快速排序线程的线程地址："<<QThread::currentThread();
    QElapsedTimer time;
    time.start();
    QVector<int> stack(high - low + 1);
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];

        int pi = partition(list, low, high);

        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
    int milsec = time.elapsed();
    qDebug()<<"快速排序总用时："<<milsec<<"毫秒";
    emit sendArray(list);
}

void Generate::working(int num)
{
    qDebug()<<"生成随机数的线程的线程地址："<<QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for(int i;i<num;++i){
        list.push_back(rand()% 100000);
    }
    int milsec = time.elapsed();
    qDebug()<<"生成"<<num<<"个随机数总用时"<<milsec<<"毫秒";
    emit sendArray(list);
}

void BubbleSort::working(QVector<int> list){
    // QVector<int>arr = m_list;
    qDebug()<<"冒泡排序线程的线程地址："<<QThread::currentThread();
    QElapsedTimer time;
    time.start();
    int n = list.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            // 如果当前元素大于下一个元素，则交换它们
            if (list[j] > list[j + 1]) {
                qSwap(list[j], list[j + 1]);
            }
        }
    }
    int milsec = time.elapsed();
    qDebug()<<"冒泡排序总用时："<<milsec<<"毫秒";
    emit sendArray(list);
}
