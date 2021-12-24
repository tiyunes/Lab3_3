#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

template<class T>
class Queue
{
public:
    Queue()
    {
        //elements = (Sequence<T>*) new LinkedListSequence<T>();
        elements = (Sequence<T>*) new ArraySequence<T>();
    }

    Queue(T* items, int size)
    {
        //this->elements = (Sequence<T>*) new LinkedListSequence<T>(items, size);
        this->elements = (Sequence<T>*) new ArraySequence<T>(items, size);
    }

    T front()
    {
        return this->elements->getFirst();
    }

    T back()
    {
        return this->elements->getLast();
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
        return this->elements->append(item);
    }

    void pop()
    {
        this->elements->pop();
    }

    ~Queue()
    {
        delete this->elements;
    }
protected:

private:
    Sequence<T>* elements;
};

#endif // QUEUE_H_INCLUDED
