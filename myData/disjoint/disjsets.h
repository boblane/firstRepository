#ifndef DISJSETS_H
#define DISJSETS_H

#include <vector>
#include <QtDebug>
using namespace std;

class DisjSets
{
private:
    vector<int> s;
public:
    enum UnionType{NORM,ELESIZE,DEPTH};
    explicit DisjSets(int numElements):s(numElements)
    {
        for (int i = 0; i < s.size(); ++i)
        {
            s[i] = -1;
        }
    }
    int find(int x) const
    {
        if(s[x]<0)
            return x;
        else
            return find(s[x]);
    }
    int find(int x)//path compression
    {
        if(s[x]<0)
            return x;
        else
            return s[x] = find(s[x]);
    }

    void unionSets(int root1, int root2, UnionType mode = ELESIZE)
    {
        if(mode == ELESIZE)//size
        {
            if(s[root2]<=s[root1])
            {

                s[root2] += s[root1];
                s[root1] = root2;
            }
            else
            {
                unionSets(root2,root1,ELESIZE);
            }
        }
        else if(mode == NORM)
        {
            s[root2] = root1;
        }
        else if(mode == DEPTH)//deep
        {
            if(s[root2]<s[root1])
                s[root1] = root2;
            else
            {
                if(s[root1]==s[root2])
                    s[root1]--;
                s[root2] = root1;
            }
        }
    }

    void print()
    {
        for(auto i:s)
            qDebug("%d\t",i);
    }
};
#endif // DISJSETS_H
