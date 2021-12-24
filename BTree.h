#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include "SEQUENCE.H"
#include "linked_list_sequence.h"
#include "array_sequence.h"
#include "BTree_node.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

template<class T>
class BTree
{
    friend class BTreeNode<T>;
public:
    BTree(int t)
    {
        this->root = nullptr;
        this->t = t;
        this->size = 0;
    }


    BTree(int t, int size, T null, function<bool(T, T)> cmp)
    {
        this->root = nullptr;
        this->t = t;
        this->size = size;
        for (int i = 0; i < size; i++)
        {
            this->insert(null, cmp);
        }
    }

    void toVector(vector<T>* v)
    {
        if (this->root != nullptr)
        {
            this->root->toVector(v);
        }
    }

    BTreeNode<T>* search(T key, function<bool(T, T)> cmp)
    {
        if (this->root != nullptr)
        {
            return this->root->search(key, cmp);
        }
        else
        {
            return nullptr;
        }
    }

    void insert(T key, function<bool(T, T)> cmp)
    {
        if (this->root == nullptr)
        {
            this->root = new BTreeNode<T>(t, true);
            root->getK()->insertAt(0, key);
            root->setN(1);
        }
        else
        {
            if (root->getN() == (2 * t - 1))
            {
                BTreeNode<T>* s = new BTreeNode<T>(t, false);
                s->getC()->set(0, root);
                s->splitC(0, root);
                int i = 0;
                if (cmp((s->getK()->get(0)), key))
                {
                    i++;
                }
                s->getC()->get(i)->insertFree(key, cmp);

                this->root = s;
            }
            else
            {
                root->insertFree(key, cmp);
            }
        }
    }

    int getT()
    {
        return this->t;
    }

    int getSize()
    {
        return this->size;
    }
private:
    BTreeNode<T>* root;
    int size;
    int t;
};


#endif // BTREE_H_INCLUDED
