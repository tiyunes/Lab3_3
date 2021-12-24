#include "sequence.H"
#include "linked_list.h"
#ifndef LINKEDLISTSEQUENCE_H
#define LINKEDLISTSEQUENCE_H

template <class T>
class LinkedListSequence: public Sequence<T>
{
public:
    friend class LinkedList<T>;

    LinkedListSequence()
    {
        this->items = new LinkedList<T>();
    }

    LinkedListSequence(T* items, int c)
    {
        this->items = new LinkedList<T>(items, c);
    }

    LinkedListSequence(int c)
    {
        this->items = new LinkedList<T>(c);
    }

    LinkedListSequence(const LinkedList<T>& l)
    {
        this->items = new LinkedList<T>(l);
    }

    LinkedListSequence(const LinkedListSequence<T>& l)
    {
        this->items = new LinkedList<T>(l.items);
    }

    T getFirst() override
    {
        return this->items->getFirst();
    }

    T getLast() override
    {
        return this->items->getLast();
    }

    T get(int index) override
    {
        return this->items->get(index);
    }

    T& getP(int index) override
    {
        T& result = (*items)[index];
        return result;
    }

    void set(int index, T item)
    {
        this->items->set(item, index);
    }

    int getLength() override
    {
        return this->items->getLength();
    }

    void append(T item) override
    {
        this->items->append(item);
    }

    void prepend(T item) override
    {
        this->items->prepend(item);
    }

    void insertAt(int index, T item) override
    {
        this->items->insertAt(index, item);
    }

    void pop() override
    {
        return this->items->pop();
    }

    void reverse() override
    {
        return this->items->reverse();
    }

    Sequence<T>* getSubsequence(int startIndex, int endIndex) override
    {
        LinkedListSequence<T>* subList = new LinkedListSequence<T>(*(this->items->getSubList(startIndex, endIndex)));
        subList->items->size = endIndex - startIndex + 1;
        return subList;
    }

    Sequence<T>* concat(Sequence <T> *l) override
    {
        Sequence<T>* concatSequence = (Sequence<T>*)new LinkedListSequence<T>();
        for (int i = 0; i < this->getLength(); i++)
        {
            concatSequence->append(this->get(i));
        }
        for (int i = 0; i < l->getLength(); i++)
        {
            concatSequence->append(l->get(i));
        }
        return concatSequence;
    }

    ~LinkedListSequence()
    {
        delete[] this->items;
    }
protected:

private:
    LinkedList<T>* items;
};

#endif // LINKEDLISTSEQUENCE_H


