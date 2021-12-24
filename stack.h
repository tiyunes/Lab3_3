#ifndef STACK_H
#define STACK_H
#include "array_sequence.h"

template<class T>
class Stack
{
public:
    Stack()
    {
        //this->elements = (Sequence<T>*) new LinkedListSequence<T>();
        this->elements = (Sequence<T>*) new ArraySequence<T>();
    }

    Stack(T* items, int size)
    {
        //this->elements = (Sequence<T>*) new LinkedListSequence<T>(items, size);
        this->elements = (Sequence<T>*) new ArraySequence<T>(items, size);
        this->elements->reverse();
    }

    Stack(Sequence<T>* elements)
    {
        this->elements = new ArraySequence<T>(elements);
    }

    T top()
    {
        return this->elements->getFirst();
    }

    bool empty()
    {
        if (this->elements->getLength() == 0) return true;
        else return false;
    }

    int getSize()
    {
        return this->elements->getLength();
    }

    void push(T item)
    {
        return this->elements->prepend(item);
    }

    void pop()
    {
        this->elements->pop();
    }

    void concat(Stack<T>* s)
    {
        for(int i = 0; i < s->elements->getLength(); i++)
        {
            this->push(s->elements->get(i));
        }
    }

    ~Stack()
    {
        delete this->elements;
    }

protected:

private:
    Sequence<T>* elements;
};

#endif // STACK_H
