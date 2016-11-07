#ifndef AVLTREE_H
#define AVLTREE_H
#include<iostream>
#include<algorithm>
#include<QtDebug>
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
    avltree()
    {
        root = nullptr;
        theSize = 0;
    }
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

private:
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
    //删除
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

        }
    }

private:
    AvlNode*    root;
    int         theSize;
};
#endif // AVLTREE_H
