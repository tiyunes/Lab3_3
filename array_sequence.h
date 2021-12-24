#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H
#include "sequence.h"
#include "dynamic_array.h"

template<class T>
class ArraySequence: public Sequence<T>
{
public:
    friend class DynamicArray<T>;

    ArraySequence();
    ArraySequence(int size);
    ArraySequence(T* items, int c);
    ArraySequence(const DynamicArray<T>& dynamicArray);
    ArraySequence(const ArraySequence<T>& arraySequence);
    ArraySequence(Sequence<T>* s);

    T getFirst() override;
    T getLast() override;
    T get(int index) override;
    T& getP(int index) override;
    void set(int index, T item) override;
    int getLength() override;
    void pop() override;

    void append(T item) override;
    void prepend(T item) override;
    void insertAt(int index, T item) override;
    void reverse() override;
    Sequence<T>* getSubsequence(int startIndex, int endIndex) override;
    Sequence<T>* concat(Sequence<T> *l) override;
    ~ArraySequence();
private:
    DynamicArray<T>* items;
};

template<class T>
ArraySequence<T>::ArraySequence()
{
    this->items = new DynamicArray<T>();
}

template<class T>
ArraySequence<T>::ArraySequence(int size)
{
    this->items = new DynamicArray<T>(size);
}

template<class T>
ArraySequence<T>::ArraySequence(T* items, int c)
{
    this->items = new DynamicArray<T>(items, c);
}

template<class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& dynamicArray)
{
    this->items = new DynamicArray<T>(dynamicArray);
}

template<class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& arraySequence)
{
    this->items = new DynamicArray<T>(arraySequence.items);
}

template<class T>
ArraySequence<T>::ArraySequence(Sequence<T>* s)
{
    this->items = new DynamicArray<T>(s->getLength());
    for (int i = 0; i < s->getLength(); i++)
    {
        items->set(i, s->get(i));
    }
}

template<class T>
T ArraySequence<T>::getFirst()
{
    return this->items->get(0);
}

template<class T>
T ArraySequence<T>::getLast()
{
    return this->items->get(this->items->size - 1);
}

template<class T>
T ArraySequence<T>::get(int index)
{
    return this->items->get(index);
}

template<class T>
T& ArraySequence<T>::getP(int index)
{
    return (*(items))[index];
}

template<class T>
void ArraySequence<T>::set(int index, T item)
{
    this->items->set(index, item);
}

template<class T>
int ArraySequence<T>::getLength()
{
    return this->items->getSize();
}

template<class T>
void ArraySequence<T>::append(T item)
{
    this->items->resize(this->items->getSize() + 1);
    this->items->set(this->items->getSize() - 1, item);
}

template<class T>
void ArraySequence<T>::prepend(T item)
{
    if (this->getLength() != 0)
    {
        DynamicArray<T>* buff = new DynamicArray<T>(this->getLength());
        for (int j = 0; j < this->getLength(); j++)
        {
            buff->values[j] = this->get(j);
        }
        this->items->size++;
        this->items = new DynamicArray<T>(this->items->size);
        this->items->set(0, item);
        for (int i = 1; i < this->getLength(); i++)
        {
            this->items->set(i, buff->get(i - 1));
        }
    }
    else
    {
        this->items->set(0, item);
        this->items->size++;
    }
}

template<class T>
void ArraySequence<T>::insertAt(int index, T item)
{
    if (index < this->getLength())
    {
        this->items->resize(this->items->size + 1);
        for (int i = 0; i < index; i++)
        {
            this->items->set(i, this->get(i));
        }
        this->items->set(index, item);
        for (int j = index + 1; j < this->getLength(); j++)
        {
            this->items->set(j, this->get(j - 1));
        }
    }

    else
    {
        T element;
        this->items->resize(index + 1);
        for (int i = 0; i < this->getLength(); i++)
        {
            this->items->set(i, this->get(i));
        }
        for (int j = this->getLength() + 1; j < index; j++)
        {
            this->items->set(j, element);
        }
        this->items->set(index, item);
    }


}

template<class T>
void ArraySequence<T>::pop()
{
    return this->items->pop();
}

template<class T>
void ArraySequence<T>::reverse()
{
    return this->items->reverse();
}

template<class T>
Sequence<T>* ArraySequence<T>::getSubsequence(int startIndex, int endIndex)
{
    ArraySequence<T>* subArray = new ArraySequence<T>(endIndex - startIndex + 1);
    for (int i = 0; i < endIndex - startIndex + 1; i++)
    {
        subArray->items->set(i, this->items->get(i + startIndex));
    }
    return subArray;
}

template<class T>
Sequence<T>* ArraySequence<T>::concat(Sequence <T> *l)
{
    Sequence<T>* concatSequence = (Sequence<T>*)new ArraySequence<T>(l->getLength() + this->getLength());
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

template<class T>
ArraySequence<T>::~ArraySequence()
{
    delete[] this->items;
}


#endif // ARRAYSEQUENCE_H


