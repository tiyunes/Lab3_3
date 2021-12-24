#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED
#include "BinaryTree.h"
#include <functional>
#include <exception>
#include <utility>
#include <iostream>

template<class TKey, class TElement>
class TPair
{
public:
    TKey key;
    TElement element;

    TPair() = default;

    TPair(TKey key, TElement element)
    {
        this->key = key;
        this->element = element;
    }

    TPair(pair<TKey, TElement> p)
    {
        this->key = p.first;
        this->element = p.second;
    }

    TKey getKey()
    {
        return this->key;
    }

    TElement& getElement()
    {
        return this->element;
    }

    void setKey(TKey key)
    {
        this->key = key;
    }

    void setElement(TElement element)
    {
        this->element = element;
    }

    bool operator==(TPair<TKey, TElement> p1)
    {
        return ((this->getKey() == p1.getKey()));
    }

    bool operator!=(TPair<TKey, TElement> &p1)
    {
        return ((this->getKey() != p1.getKey()));
    }
};

template<class TKey, class TElement>
class IDictionary
{
    friend class TPair<TKey, TElement>;

private:
    BinaryTree<TPair<TKey, TElement>>* tree;
    function<bool(TPair<TKey, TElement>, TPair<TKey, TElement>)> cmp;

public:
    IDictionary()
    {
        this->tree = new BinaryTree<TPair<TKey, TElement>>();
    }

    IDictionary(function<bool(TPair<TKey, TElement>, TPair<TKey, TElement>)> cmp)
    {
        this->tree = new BinaryTree<TPair<TKey, TElement>>();
        this->cmp = cmp;
    }

    IDictionary(int n, function<bool(TPair<TKey, TElement>, TPair<TKey, TElement>)> cmp)
    {
        this->tree = new BinaryTree<TPair<TKey, TElement>>(n, cmp);
        this->setCmp(cmp);
    }

    IDictionary(IDictionary<TKey, TElement>* d)
    {
        this->tree = new BinaryTree<TPair<TKey, TElement>>(d->getTree());
        this->setCmp(d->getCmp());
    }

    int getCount()
    {
        return this->tree->getS();
    }

    BinaryTree<TPair<TKey, TElement>>* getTree()
    {
        return this->tree;
    }

    function<bool(TPair<TKey, TElement>, TPair<TKey, TElement>)> getCmp()
    {
        return this->cmp;
    }

    bool containsKey(TKey key)
    {
        TPair<TKey, TElement> p;
        p.setKey(key);
        if (this->tree->contains(p, cmp) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool containsElement(TElement element)
    {
        TPair<TKey, TElement> p;
        p.setElement(element);
        if (this->tree->contains(p, cmp) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    TElement& get(TKey key)
    {
        TPair<TKey, TElement> p;
        p.setKey(key);
        if (this->tree->contains(p, cmp) == 1)
        {
            return (this->tree->Find(p, cmp))->get().getElement();
        }
        else
        {
            throw std::out_of_range("Invalid key");
        }
    }

    void setCmp(function<bool(TPair<TKey, TElement>, TPair<TKey, TElement>)> cmp)
    {
        this->cmp = cmp;
    }

    void add(TKey key, TElement element)
    {
        TPair<TKey, TElement> p;
        p.setKey(key);
        p.setElement(element);
        this->tree->add(p, cmp);
    }

    void add(TPair<TKey, TElement> p)
    {
        this->tree->add(p, cmp);
    }

    void remove(TKey key)
    {
        TPair<TKey, TElement> p;
        p.setKey(key);
        if (this->tree->contains(p, cmp) == 1)
        {
            this->tree->remove(p, cmp);
        }
        else
        {
            throw std::out_of_range("Invalid key");
        }
    }


    void increase(TKey key)
    {
        TPair<TKey, TElement> p;
        p.setKey(key);
        if (this->tree->contains(p, cmp) == 1)
        {
            this->get(key)++;
        }
        else
        {
            throw std::out_of_range("Invalid key");
        }
    }

    ~IDictionary<TKey, TElement>()
    {
        if (this->tree != nullptr)
        {
            delete tree;
        }
    }


};


#endif // DICTIONARY_H_INCLUDED
