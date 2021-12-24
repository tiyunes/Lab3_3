#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "linked_list.h"
#include "dynamic_array.h"

template <class T>
class Sequence
{
public:
    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(int index) = 0;
    virtual T& getP(int index) = 0;
    virtual void set(int index, T item) = 0;
    virtual Sequence <T>* getSubsequence(int startIndex, int endIndex) = 0;
    virtual int getLength() = 0;

    virtual void append(T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insertAt(int index, T item) = 0;
    virtual void pop() = 0;
    virtual void reverse() = 0;
    virtual Sequence<T>* concat(Sequence<T> *l) = 0;
    //virtual ~Sequence<T>() = default;
};
#endif // SEQUENCE_H
