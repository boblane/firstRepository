#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <QtDebug>
#include <string>
#include "Hash/mrprime.h"

using namespace std;

template<typename HashedObj>
class HashTable
{
private:
    enum EntryType{ACTIVE,EMPTY,DELETED};
    struct HashEntry
    {
        HashedObj element;
        EntryType info;
        HashEntry(const HashedObj &e = HashedObj(),EntryType i = EMPTY):
            element(e),info(i){}
    };
public:
    explicit HashTable(int size = 101):array(nextPrime(size))
    {
        makeEmpty(array);
    }
    bool contains(const HashedObj &x) const
    {
        return isActive(myhash(x));
    }

    void makeEmpty(vector<HashEntry> &arr)
    {
        currentSize = 0;
        for(int i = 0;i!=arr.size();++i)
        {
            arr[i].info = EMPTY;
        }
    }

    bool insert(const HashedObj &x)
    {
        int currentPos = findPos(x);
        if(isActive(currentPos))
            return false;
        array[currentPos]= HashEntry(x,ACTIVE);

        if(++currentSize > array.size()/2)
            rehash();
        return true;
    }

    bool remove(const HashedObj &x)
    {
        int currentPos = findPos(x);
        if(!isActive(currentPos))
            return false;
        array[currentPos].info = DELETED;
        currentSize--;
        return true;
    }

    void printHashTable()
    {
        for(int i = 0; i!= array.size();++i)
            if(array[i].info == ACTIVE)
                qDebug("%d -- %d",i,array[i].element);
    }

private:
    vector<HashEntry> array;
    int currentSize;

    bool isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }

    int findPos(const HashedObj &x) const
    {
        int offset = 1;
        int currentPos = myhash(x);
        while ((array[currentPos].info != EMPTY)&&
               array[currentPos].element!=x)
        {
            currentPos += offset;
            offset += 2;
            if(currentPos >= array.size())
                currentPos -= array.size();
        }
        return currentPos;
    }

    void rehash()
    {
        vector<HashEntry> oldArray = array;
        array.resize(nextPrime(2*oldArray.size()));
        makeEmpty(array);

        for(int i = 0;i!=oldArray.size();++i)
            if(oldArray[i].info == ACTIVE)
                insert(oldArray[i].element);
    }

    int myhash(const HashedObj &x) const
    {
        if(string(typeid(x).name())== "int")
        {
//            qDebug()<<"hehe";
            return x%array.size();
        }
    }
};

#endif // HASHTABLE_H
