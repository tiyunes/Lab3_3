#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED
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
        return ((this->GetKey() == p1.GetKey()));
    }

    bool operator!=(TPair<TKey, TElement> &p1)
    {
        return ((this->GetKey() != p1.GetKey()));
    }

    void operator =(TPair<TKey, TElement> &p1)
    {
        this->setKey(p1.getKey());
        this->setElement(p1.getElement());
    }
};


#endif // DICTIONARY_H_INCLUDED
