#include "mythread.h"
#include<QElapsedTimer>
#include<QDebug>
Generate::Generate(QObject *parent)
    : QThread{parent}
{}
BubbleSort::BubbleSort(QObject *parent)
    : QThread{parent}
{}
QuickSort::QuickSort(QObject *parent)
    : QThread{parent}
{}

void QuickSort::recvNum(QVector<int> list)
{
    m_list = list;
}

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

void QuickSort::run()
{
    int low =0;
    int high =m_list.size()-1;
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

        int pi = partition(m_list, low, high);

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
    emit sendArray(m_list);
}
void Generate::recvNum(int num)
{
    m_num = num;
}

void Generate::run()
{
    qDebug()<<"生成随机数的线程的线程地址："<<QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for(int i;i<m_num;++i){
        list.push_back(rand()% 100000);
    }
    int milsec = time.elapsed();
    qDebug()<<"生成"<<m_num<<"个随机数总用时"<<milsec<<"毫秒";
    emit sendArray(list);
}

void BubbleSort::recvNum(QVector<int> list)
{
    m_list = list;
}

void BubbleSort::run(){
    // QVector<int>arr = m_list;
    qDebug()<<"冒泡排序线程的线程地址："<<QThread::currentThread();
    QElapsedTimer time;
    time.start();
    int n = m_list.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            // 如果当前元素大于下一个元素，则交换它们
            if (m_list[j] > m_list[j + 1]) {
                qSwap(m_list[j], m_list[j + 1]);
            }
        }
    }
    int milsec = time.elapsed();
    qDebug()<<"冒泡排序总用时："<<milsec<<"毫秒";
    emit sendArray(m_list);
}
