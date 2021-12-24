#ifndef BINARY_HEAP_H_INCLUDED
#define BINARY_HEAP_H_INCLUDED
#include "sequence.H"
#include "array_sequence.h"
#include "dictionary.h"

template<typename T>
class Heap
{
private:
    Sequence<T>* s;
    int capacity;
    int size;
    function<bool(T, T)> cmp;

public:
    Heap()
    {
        this->s = (Sequence<T>*) new ArraySequence<T>();
        this->capacity = 0;
        this->size = 0;
    }

    Heap(function<bool(T, T)> cmp)
    {
        this->s = (Sequence<T>*) new ArraySequence<T>();
        this->capacity = 0;
        this->size = 0;
        this->cmp = cmp;
    }

    Heap(int capacity, function<bool(T, T)> cmp)
    {
        this->s = (Sequence<T>*) new ArraySequence<T>();
        this->capacity = capacity;
        this->size = 0;
        this->cmp = cmp;
    }

    T get(int index)
    {
        this->s->get(index);
    }

    void buildHeap(Sequence<T>* s1, function<bool(T, T)> cmp)
    {
        this->s = (Sequence<T>*) new ArraySequence<T>(s1);
        this->size = s1->getLength();
        this->capacity = s1->getLength();
        this->cmp = cmp;
        for (int i = s1->getLength() / 2 - 1; i >= 0; i--)
        {
            this->minHeapify(i);
        }
    }

    void insert(T value)
    {
        if (size == capacity)
        {
            doubleCapacity(value);
        }
        size++;
        int i = size - 1;
        this->s->insertAt(i, value);
        while (i != 0 && cmp(s->get(i),s->get(parent(i))))
        {
            swap(&s->getP(i), &s->getP(parent(i)));
            i = parent(i);
        }
    }

    void decrease(int i, T value)
    {
        s->insertAt(value, i);
        while(i != 0 && cmp(s->get(i),s->get(parent(i))))
        {
            swap(&s->get(i), &s->get(parent(i)));
            i = parent(i);
        }
    }

    Sequence<T>* getSequence()
    {
        return this->s;
    }

    T top()
    {
        return s->get(0);
    }

    T extractMin()
    {
        if (size <= 0)
        {
            TPair<T, int> p;
            return p.getKey();
        }
        if (size == 1)
        {
            size--;
            return s->get(0);
        }

        T root = s->get(0);
        s->set(0, s->get(size - 1));
        size--;
        this->minHeapify(0);
        return root;
    }

    void deleteValue(int i)
    {
        this->decrease(i, INT_MIN);
        this->extractMin();
    }

    void minHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < size && cmp(s->get(l),s->get(i)))
        {
            smallest = l;
        }
        if (r < size && cmp(s->get(r),s->get(smallest)))
        {
            smallest = r;
        }
        if (smallest != i)
        {
            swap(&s->getP(i), &s->getP(smallest));
            this->minHeapify(smallest);
        }
    }

    void doubleCapacity(T value)
    {
        if (this->s == nullptr)
        {
            this->s = (Sequence<T>*) new ArraySequence<T>(1);
            this->capacity = 1;
            this->size = 0;
            return;
        }
        int newCapacity = 2 * this->capacity;
        Sequence<T>* newS = (Sequence<T>*) new ArraySequence<T>(newCapacity);
        for (int i = 0; i < this->size; i++)
        {
            newS->set(i, s->get(i));
        }
        if (this->s != nullptr)
        {
            delete this->s;
        }
        this->capacity = newCapacity;
        this->size = size;
        this->s = newS;
    }

    T getMin()
    {
        return this->s->get(0);
    }

    int search(T value, int index = 0)
    {
        if (this->size == 0)
        {
            return -1;
        }

        if (this->s->get(index) == value)
        {
            return index;
        }

        if ((2 * index + 1) < size && cmp(value, this->s->get(left(index))))
        {
            int res = this->search(value, left(index));
            if (res != -1)
            {
                return res;
            }
        }
        if (right(index) < size && cmp(value, this->s->get(right(index))))
        {
            return this->search(value, right(index));
        }
        return -1;
    }

    template<typename K>
    K searchKey(TPair<K, T> p, int index = 0)
    {
        for (int i = 0; i < size; i++)
        {
            if (p.getElement() == this->s->get(i).getElement)
            {
                return this->s->get(i).getKey();
            }
        }
    }

    bool contains(T value)
    {
        if (this->search(value) != -1)
        {
            return true;
        }
        else return false;
    }

    void swap(T* x, T* y)
    {
        T temp = *x;
        *x = *y;
        *y = temp;
    }

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int left(int i)
    {
        return 2 * i + 1;
    }

    int right(int i)
    {
        return 2 * i + 2;
    }

    int getSize()
    {
        return this->size;
    }
};

#endif // BINARY_HEAP_H_INCLUDED
