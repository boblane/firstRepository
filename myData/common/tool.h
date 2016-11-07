#ifndef TOOL_H
#define TOOL_H
#include<vector>
#include<iostream>
#include<Qstring>

template <typename Comparable>
void printVector(const std::vector<Comparable> &arr)
{
    for(auto a:arr)
    {
        qDebug()<<a;
    }
}

#endif // TOOL_H
