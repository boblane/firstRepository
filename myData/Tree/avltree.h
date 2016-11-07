#ifndef AVLTREE_H
#define AVLTREE_H
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<math.h>
#include<QtDebug>
using namespace std;

template <typename Comparable>
class avltree
{
private:
    struct AvlNode
    {
        Comparable element;
        AvlNode*    left;
        AvlNode*    right;
        int         height;
        AvlNode(const Comparable &theElement, AvlNode *lt, AvlNode *rt, int h = 0):
            element(theElement),left(lt),right(rt),height(h){}
    };
public:
    avltree(int _radius = 10,int _hGap = 150, int _vGap = 80, int _width = 640, int _height = 480):
        radius(_radius),hGap(_hGap),vGap(_vGap),canvasWidth(_width),canvasHeight(_height)
    {
        //        root = new AvlNode(NULL,nullptr,nullptr);
        root = nullptr;
        theSize = 0;
    }
    //数据操作
    void insert(const Comparable &x)
    {
        insert(x, root);
    }
    void remove(const Comparable &x)
    {
        remove(x, root);
    }
    int Size() const
    {
        return theSize;
    }
    void printTree(avltree *tree)
    {
        print(tree->root);
    }

    AvlNode * getRoot()
    {
        return root;
    }

    void setRoot(AvlNode *_root)
    {
        root = _root;
    }

    void copyTo(avltree * _dst)
    {
        AvlNode *p = new AvlNode(NULL,nullptr,nullptr);
        p = copy(root);
        _dst->setRoot(p);
    }
    //获得几何信息
    void getPointsAndLines(avltree *tree, map<int,QPoint> &_points, QVector<QLine> &_lines)
    {
        AvlNode *t = tree->getRoot();
        if(t!=nullptr)
        {
            display(t,canvasWidth/2,canvasHeight/10,hGap, _points, _lines);
        }
    }

private:
    void print(AvlNode *t)
    {
        if(t == nullptr)
            return;
        print(t->left);
        std::cout<<t->element<<std::endl;
        print(t->right);
    }
    //当前节点的高度
    int Height(AvlNode *t) const
    {
        return t==nullptr?-1:t->height;
    }
    //单旋转
    void rotateWithLeftChild(AvlNode* &k2)
    {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(Height(k2->left),Height(k2->right))+1;
        k1->height = std::max(Height(k1->left),k2->height)+1;
        k2 = k1;
    }
    void rotateWithRightChild(AvlNode* &k2)
    {
        AvlNode* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = std::max(Height(k2->left),Height(k2->right))+1;
        k1->height = std::max(Height(k1->right),k2->height)+1;
        k2 = k1;
    }
    //双旋转
    void doubleWithLeftChild(AvlNode* &k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }
    void doubleWithRightChild(AvlNode* &k3)
    {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }

    //插入
    void insert(const Comparable &x, AvlNode* &t)
    {
        if(t == nullptr)
        {
            t = new AvlNode(x,nullptr,nullptr);
            ++ theSize;
        }
        else if(x<t->element)
        {
            insert(x,t->left);
            if(Height(t->left)-Height(t->right)==2)
            {
                if(x<t->left->element)
                    rotateWithLeftChild(t);
                else
                    doubleWithLeftChild(t);
            }
        }
        else if(x>t->element)
        {
            insert(x,t->right);
            if(Height(t->right)-Height(t->left)==2)
            {
                if(x>t->right->element)
                    rotateWithRightChild(t);
                else
                    doubleWithRightChild(t);
            }
        }
        else
            ;
        t->height = std::max(Height(t->left),Height(t->right))+1;
    }
    //删除部分
    //删除时的高度调整
    void delFixedUp(AvlNode* &t)
    {
        if(Height(t->left)>Height(t->right))
        {
            if(Height(t->left->left)>=Height(t->right->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
        else
        {
            if(Height(t->right->right)>=Height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
    }
    //删除含有两个子树的节点
    void delTwoChild(AvlNode* &t, AvlNode* &node)
    {
        if(t->left!=nullptr)
        {
            delTwoChild(t->left,node);
            if(std::abs(Height(t->left)-Height(t->right))>=2)
                delFixedUp(t);
            t->height=std::max(Height(t->left),Height(t->right))+1;
        }
        else
        {
            node->element = t->element;
            AvlNode *oldNode = t;
            t = t->right;
            delete oldNode;
        }
    }

    //删除已经找到的节点
    void delElement(AvlNode* &t)
    {
        if(t->left == nullptr)//只有右子树或者全为空
        {
            AvlNode *oldNode = t;
            t = t->right;
            delete oldNode;
        }
        else if(t->left!=nullptr && t->right==nullptr)//只有左子树
        {
            AvlNode *oldNode = t;
            t = t->left;
            delete oldNode;
        }
        else if (t->left!=nullptr && t->right!=nullptr) //删除节点含有左右子树
        {
            delTwoChild(t->right,t);
        }
        if(t!=nullptr)
        {
            t->height = std::max(Height(t->left),Height(t->right))+1;
            if(std::abs(Height(t->left)-Height(t->right))>=2)
            {
                delFixedUp(t);
                t->height=std::max(Height(t->left),Height(t->right))+1;
            }
        }
    }

    void remove(const Comparable &x, AvlNode* &t)
    {
        if(t == nullptr)
        {
            std::cerr<<"can't find the element!"<<std::endl;
            return;
        }
        else if (t!=nullptr&&x == t->element)
        {
            delElement(t);
        }
        else if(t!=nullptr)
        {
            if(x<t->element)
                remove(x,t->left);
            else
                remove(x,t->right);
            if(std::abs(Height(t->left)-Height(t->right))>=2)
            {
                delFixedUp(t);
            }
            t->height=std::max(Height(t->left),Height(t->right))+1;
        }

    }
    //copy
    AvlNode* copy(const AvlNode* _src)
    {
        if(_src == nullptr)
            return  nullptr;
        else
        {
            AvlNode*  _dst = new AvlNode(NULL,nullptr,nullptr);
            _dst->element = _src->element;
            _dst->left = copy(_src->left);
            _dst->right = copy(_src->right);
            return _dst;
        }
    }
    //画树
    void display(AvlNode *t, int x, int y, int _hGap, map<int,QPoint> &_points, QVector<QLine> &_lines)
    {
        _points[t->element]=QPoint(x,y);
        if(t->left!=nullptr)
        {
            connectLeftChild(x,y,x-_hGap,y+vGap,_lines);
            display(t->left,x-_hGap,y+vGap,_hGap/2,_points,_lines);
        }
        if(t->right!=nullptr)
        {
            connectRightChild(x,y,x+_hGap,y+vGap,_lines);
            display(t->right,x+_hGap,y+vGap,_hGap/2,_points,_lines);
        }
    }
    void connectLeftChild(int x1,int y1,int x2,int y2,QVector<QLine> &_lines)
    {
        double d=sqrt(vGap*vGap+(x2-x1)*(x2-x1));
        int x11=(int)(x1-radius*(x1-x2)/d);
        int y11=(int)(y1+radius*vGap/d);
        int x21=(int)(x2+radius*(x1-x2)/d);
        int y21=(int)(y2-radius*vGap/d);
        _lines.push_back(QLine(x11,y11,x21,y21));
    }
    void connectRightChild(int x1,int y1,int x2,int y2,QVector<QLine> &_lines)
    {
        double d=sqrt(vGap*vGap+(x2-x1)*(x2-x1));
        int x11=(int)(x1+radius*(x2-x1)/d);
        int y11=(int)(y1+radius*vGap/d);
        int x21=(int)(x2-radius*(x2-x1)/d);
        int y21=(int)(y2-radius*vGap/d);
        _lines.push_back(QLine(x11,y11,x21,y21));
    }

private:
    AvlNode*    root;
    int         theSize;
    int         radius;
    int         hGap;
    int         vGap;
    int         canvasWidth;
    int         canvasHeight;
    map<int,QPoint>    nodeCord;
    vector<QLine>      lines;
};
#endif // AVLTREE_H
