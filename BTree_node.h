#ifndef BTREE_NODE_H_INCLUDED
#define BTREE_NODE_H_INCLUDED
#include "SEQUENCE.H"
#include <utility>
#include <functional>
#include <vector>

template<class T>
class BTreeNode
{
    //friend class BTree<T>;
private:
    Sequence<T>* k;
    Sequence<BTreeNode<T>*>* c;
    int t;
    int sizeNode;
    bool leaf = 0;

public:
    BTreeNode()
    {
        this->k = new ArraySequence<T>();
        this->c = new ArraySequence<BTreeNode<T>*>();
        this->sizeNode = 0;
    }

    BTreeNode(bool leaf)
    {
        this->leaf = leaf;
    }

    BTreeNode(T item)
    {
        this->k->Add(item);
        this->sizeNode++;
    }

    BTreeNode(Sequence<T>* k, BTreeNode<T>** c, int t, int sizeNode, bool leaf)
    {
        this->k = new ArraySequence<T>(k);
        this->c = new ArraySequence<BTreeNode<T>*>(2 * t);
        this->c = c;
        this->t = t;
        this->sizeNode = sizeNode;
        this->leaf = leaf;
    }

    BTreeNode(BTreeNode<T>* n)
    {
        this->k = n->k;
        this->c = n->c;
        this->sizeNode = n->sizeNode;
        this->t = n->sizeNode;
        this->leaf = n->leaf;
    }

    BTreeNode(BTreeNode<T>& n)
    {
        this->k = n.k;
        this->c = n.c;
        this->sizeNode = n.sizeNode;
        this->t = n.sizeNode;
        this->leaf = n.leaf;
    }

    BTreeNode (int t, bool leaf)
    {
        this->t = t;
        this->leaf = leaf;
        this->k = new ArraySequence<T>(2 * t - 1);
        this->c = new ArraySequence<BTreeNode<T>*>(2 * t);
        this->sizeNode = 0;
    }

    Sequence<T>* getK()
    {
        return this->k;
    }

    Sequence<BTreeNode<T>*>* getC()
    {
        return this->c;
    }

    int getN()
    {
        return this->sizeNode;
    }

    void setN(int n)
    {
        this->sizeNode = n;
    }

    void toVector(vector<T>* v)
    {
        int i = 0;
        for (i = 0; i < sizeNode; i++)
        {
            if (this->leaf == false)
            {
                if (c->get(i) != nullptr && c != nullptr)
                {
                    c->get(i)->toVector(v);
                }
            }
            v->push_back(this->getK()->get(i));
        }

        if(this->leaf == false)
        {
            if (c != nullptr && c->get(i) != nullptr)
            {
                c->get(i)->toVector(v);
            }
        }
    }

    BTreeNode<T>* search(T key, function<bool(T, T)> cmp)
    {
        int i = 0;

        while (i < this->sizeNode && cmp(this->k->get(i), key))
        {
            i++;
        }

        if (this->k->get(i) == key)
        {
            return this;
        }

        if (leaf == true)
        {
            return nullptr;
        }
        return c->get(i)->search(key, cmp);
    }

    void insertFree(T key, function<bool(T, T)> cmp)
    {
        int i = sizeNode - 1;
        if (leaf == true)
        {
            while (i >= 0 && cmp(key, k->get(i)))
            {
                k->set(i + 1, k->get(i));
                i--;
            }
            k->set(i + 1, key);
            sizeNode++;
        }

        else
        {
            while (i >= 0 && cmp(key, k->get(i)))
            {
                i--;
            }
            if (c->get(i + 1)->getN() == (2 * t - 1))
            {
                this->splitC(i + 1, c->get(i + 1));
                if (cmp(k->get(i + 1), key))
                {
                    i++;
                }
            }
            c->get(i + 1)->insertFree(key, cmp);
        }
    }

    void splitC(int i, BTreeNode<T>* n1)
    {
        BTreeNode<T>* n2 = new BTreeNode(n1->t, n1->leaf);
        n2->sizeNode = (t - 1);
        for (int j = 0; j < (t - 1); j++)
        {
            n2->k->set(j, n1->k->get(j + t));
        }
        if (n1->leaf == false)
        {
            for (int j = 0;  j < t; j++)
            {
                n2->c->set(j, n1->c->get(j + t));
            }
        }

        n1->setN(t - 1);

        for (int j = this->sizeNode; j >= (i + 1); j--)
        {
            c->set(j + 1, c->get(j));
        }

        c->set(i + 1, n2);

        for (int j = (this->sizeNode - 1); j >= i; j--)
        {
            k->set(j + 1, k->get(j));
        }

        k->set(i, n1->getK()->get(t - 1));
        this->sizeNode++;
    }
};


#endif // BTREE_NODE_H_INCLUDED
