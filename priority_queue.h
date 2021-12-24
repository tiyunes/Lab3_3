#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED
#include "sequence.h"
#include "binary_heap.h"
#include "dictionary.h"

template<class K, class T>
class PriorityQueue
{
private:
    Heap<TPair<K, T>>* h;
    int size;
    function<bool(TPair<K, T>, TPair<K, T>)> cmp;

    K searchKey(T item)
    {
        K bufPriority;
        TPair<K, T> p(bufPriority, item);
        return this->h->searchKey();
    }

public:
    PriorityQueue()
    {
        this->size = 0;
        this->h = new Heap<TPair<K, T>>();
    }

    PriorityQueue(function<bool(TPair<K, T>, TPair<K, T>)> cmp)
    {
        this->cmp = cmp;
        this->h = new Heap<TPair<K, T>>(cmp);
        this->size = 0;
    }

    PriorityQueue(Sequence<TPair<K, T>>* s, function<bool(TPair<K, T>, TPair<K, T>)> cmp)
    {
        this->cmp = cmp;
        this->size = s->getLength();
        this->h = new Heap<TPair<K, T>>(cmp);
        this->h->buildHeap(s, cmp);
    }

    int getSize()
    {
        return this->size;
    }

    T peek(int index)
    {
        return h->get(index).getKey();
    }

    T peekFirst()
    {
        return this->h->top().getElement();
    }

    void enqueue(K priority, T item)
    {
        TPair<K, T> p(priority, item);
        this->h->insert(p);
        this->size++;
    }

    T dequeue()
    {
        this->size--;
        return this->extractMin().getElement();
    }

    void pop(T item)
    {
        K priority;
        TPair<K, T> p(priority, item);
        if (this->h->contains(p))
        {
            this->h->deleteValue(this->h->search());
        }
        this->size--;
    }

    TPair<K, T> extractMin()
    {
        this->size--;
        return this->h->extractMin();
    }
};


#endif // PRIORITY_QUEUE_H_INCLUDED
