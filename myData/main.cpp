#include "dialog.h"
#include <QApplication>
#include <iostream>
#include <QtDebug>
#include <QString>
#include "Tree/avltree.h"
#include "Hash/mrprime.h"
#include "Hash/hashtable.h"
#include "common/tool.h"
#include "sort/insertionsort.h"
#include "disjoint/disjsets.h"
#include "test/solution.h"
using namespace std;

int lastNonZeroOfArr(int *p, int size)
{
    int i = size - 1;
    for (; i >= 0; --i)
    {
        if (*(p + i) != 0)
        {
            return *(p + i);
        }
    }
    return *p;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
//    w.show();
    vector<int> arr{4,2,1,3};
    printVector(arr);
    qDebug()<<"---------";
    insertionSort(arr.begin(),arr.end());
    printVector(arr);
    qDebug()<<"---------";
//    HashTable<int> myhash(4);
//    myhash.insert(6);
//    myhash.insert(16);
//    myhash.insert(26);
//    myhash.printHashTable();
    Solution so;
    vector<int> A{1,2,4,7,3,5,6,8};
    vector<int> B{4,7,2,1,5,3,8,6};
    so.reConstructBinaryTree(A,B);
    return a.exec();
}
