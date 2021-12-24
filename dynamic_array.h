#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

template<class T>
class DynamicArray
{
public:
    DynamicArray();
    DynamicArray(T* items, int size);
    DynamicArray(int size);
    DynamicArray(const DynamicArray<T>& dynamicArray);

    T get(int index);
    int getSize();
    T& operator[] (int index);
    void pop();
    void reverse();

    void set(int index, T value);
    void resize(int newSize);
    void changeSize(int newSize);
    ~DynamicArray();

protected:

public:
    T* values;
    int size;
};

template<class T>
DynamicArray<T>::DynamicArray()
{
    this->values = new T[0];
    this->size = 0;
}

template<class T>
DynamicArray<T>::DynamicArray(int size)
{
    this->values = new T[size];
    T item;
    for (int i = 0; i < size; i++)
    {
        this->values[i] = item;
    }
    this->size = size;
}

template<class T>
DynamicArray<T>::DynamicArray(T* items, int size)
{
    this->values = new T[size];
    for (int i = 0; i < size; i++)
    {
        this->values[i] = items[i];
    }
    this->size = size;
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray)
{
    this->size = dynamicArray.size;
    this->values = new T[dynamicArray.size];
    for (int i = 0; i < dynamicArray.size; i++)
    {
        this->values[i] = dynamicArray.values[i];
    }
}

template<class T>
T DynamicArray<T>::get(int index)
{
    if (index < 0 || index > this->getSize())
    {
        throw std::out_of_range("Invalid index");
    }
    return this->values[index];
}

template<class T>
int DynamicArray<T>::getSize()
{
    return this->size;
}

template<class T>
T& DynamicArray<T>::operator[](int index)
{
    return this->values[index];
}

template<class T>
void DynamicArray<T>::set(int index, T value)
{
    if (index < 0 || index > this->getSize())
    {
        throw std::out_of_range("Invalid index");
    }
    this->values[index] = value;
}

template<class T>
void DynamicArray<T>::resize(int newSize)
{
    if(this->size > 0)
    {
        int i;
        T *newValues = new T[newSize];
        T item;
        for (i = 0; i < this->getSize(); i++)
        {
            newValues[i] = this->get(i);
        }
        if (newSize > this->size)
        {
            for (int j = this->size; j < newSize; j++)
            {
                newValues[j] = item;
            }
        }
        this->size = newSize;
        this->values = new T[newSize];
        for (i = 0; i < newSize; i++)
        {
            this->values[i] = newValues[i];
        }
    }
    else
    {
        T item;
        this->size = newSize;
        this->values = new T[newSize];
        for (int j = 0; j < newSize; j++)
        {
            this->values[j] = item;
        }
    }

}

template<class T>
void DynamicArray<T>::changeSize(int newSize)
{
    this->size = newSize;
}

template<class T>
void DynamicArray<T>::pop()
{
    T *newValues = new T[this->size - 1];
    if (this->size - 1 != 0)
    {
        for (int i = 0; i < this->size - 1; i++)
        {
            newValues[i] = this->get(i + 1);
        }
        this->changeSize(this->size - 1);
        this->values = new T[this->size];
        for (int j = 0; j < this->size; j++)
        {
            this->values[j] = newValues[j];
        }
    }
    else if (this->size == 1)
    {
        this->changeSize(0);
        this->values = new T[0];
    }

}

template<class T>
void DynamicArray<T>::reverse()
{
    T buff;
    for (int i = 0; i < (this->getSize() / 2); i++)
    {
        buff = this->get(i);
        this->values[i] = this->get(this->getSize() - i - 1);
        this->values[this->getSize() - i - 1] = buff;
    }
}

template<class T>
DynamicArray<T>::~DynamicArray()
{
    delete[] this->values;
}

#endif // DYNAMICARRAY_H


