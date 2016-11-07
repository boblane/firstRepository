#ifndef SOLUTION_H
#define SOLUTION_H
#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

//class Solution
//{
//public:
//    Solution();
//    void getMinMaxs(vector<int> &data)
//    {
//        for (int i = 1; i < data.size()-1; ++i)
//        {
//            if((data[i]>=data[i-1])&&(data[i]>=data[i+1]))
//                maxs.push_back(make_pair(data[i],i));
//            if((data[i]<=data[i-1])&&(data[i]<=data[i+1]))
//                mins.push_back(make_pair(data[i],i));
//            if((data[i]==data[i-1])&&(data[i]==data[i+1]))
//                continue;
//        }
//    }


//    vector<pair<int,int>>::iterator findNext(pair<int,int> day1,vector<pair<int,int>> &date)
//    {
//        auto it = date.begin();
//        for(;it!=date.end();++it)
//        {
//            if(day1.second<(*it).second)
//                return it;
//        }
//        return it;
//    }

//    vector<pair<int,int>>::iterator findBefore(pair<int,int> day1,vector<pair<int,int>> &date)
//    {
//        auto it = date.begin();
//        for(;it!=date.end();++it)
//        {
//            if(day1.second<(*it).second)
//                return --it;
//        }
//        return it;
//    }

//    pair<int,int> MaxElement(vector<pair<int,int>>::iterator begin,
//                             vector<pair<int,int>>::iterator end)
//    {
//        PairFirstComp cmp;
//        return *max_element(begin,end,cmp);
//    }

//    pair<int,int> MinElement(vector<pair<int,int>>::iterator begin,
//                             vector<pair<int,int>>::iterator end)
//    {
//        PairFirstComp cmp;
//        return *min_element(begin,end,cmp);
//    }

//    int calculateDelta(void)
//    {
//        if(mins.size()==0||maxs.size()==0)
//            return 0;
//        if(mins.size()==1)
//        {
//            if((maxs.size()==1)&&(mins[1].second>maxs[2].second))
//                return 0;
//            else
//            {
//                max1 = MaxElement(findNext(mins[0],maxs),maxs.end());
//                return max1.first-mins[0].first;
//            }
//        }
//        return 1;
//    }

//    int calculateMax(vector<int> prices)
//    {
//        vector<int> data(prices);
//        data.insert(data.begin(),prices[1]);
//        data.push_back(prices[prices.size()-2]);
//        getMinMaxs(data);
//        calculateDelta();
//        return 1;
//    }
//private:
//    class PairFirstComp
//    {
//    public:
//        bool operator()(pair<int,int> i,pair<int,int> j)
//        {
//            return i.first<=j.first;
//        }
//    };
//    vector<pair<int,int>> mins;
//    pair<int,int> min1;
//    pair<int,int> min2;
//    vector<pair<int,int>> maxs;
//    pair<int,int> max1;
//    pair<int,int> max2;

//};


class Solution {
public:
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    struct TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> in)
    {
        if(pre.empty())
            return nullptr;
        root = new TreeNode(pre[0]);
        buildChild(pre,in,root);
        return root;
    }

    void buildChild(vector<int> pre,vector<int> in,struct TreeNode* &t)
    {
        vector<int> lin,rin;
        vector<int> lpre,rpre;
        vector<int>::iterator it;
        if(in.size()==0)//单节点
            return;
        auto p = find(in.begin(),in.end(),pre.front());
        if(p!=in.end())//找到
        {
            t = new TreeNode(pre.front());
            for(it = in.begin();it!=p;++it)
            {
                lin.push_back(*it);
                lpre.push_back(pre[it-in.begin()+1]);
            }
            for(it = p+1;it!=in.end();++it)
            {
                rin.push_back(*it);
                rpre.push_back(pre[it-in.begin()]);
            }
        }
        buildChild(lpre,lin,t->left);
        buildChild(rpre,rin,t->right);
    }

private:
    TreeNode *root;
};
#endif // SOLUTION_H
