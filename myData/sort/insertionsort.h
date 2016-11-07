#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include<vector>
#include<functional>

template <typename Comparable>
void insertionSort(std::vector<Comparable> &a)
{
    int j;
    for(int p = 1;p!=a.size();++p)
    {
        Comparable temp = a[p];
        for(j = p;j>0&&temp<a[j-1];j--)
        {
            a[j] = a[j-1];
        }
        a[j] =temp;
    }
}

template <typename Iterator>
void insertionSort(const Iterator &begin, const Iterator &end)
{
    if(begin!=end)
        insertionSortHelp(begin,end,*begin);
}


template <typename Iterator, typename Object>
void insertionSortHelp(const Iterator &begin, const Iterator &end, const Object &obj)
{
    insertionSort(begin,end,std::greater<Object>());
}



template <typename Iterator, typename Comparator, typename Object>
void insertionSort(const Iterator &begin, const Iterator &end, Comparator Lessthan ,const Object &obj)
{
    Iterator j;
    for(Iterator p = begin + 1;p!=end;++p)
    {
        Object temp = *p;
        for(j = p;j!=begin&&Lessthan(temp,*(j-1));--j)
            *j = *(j-1);
        *j = temp;
    }
}

template <typename Iterator,typename Comparator>
void insertionSort(const Iterator &begin, const Iterator &end, Comparator Lessthan)
{
    if(begin!=end)
        insertionSort(begin,end,Lessthan,*begin);
}
#endif // INSERTIONSORT_H
