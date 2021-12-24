#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdexcept>
#include <iostream>

using namespace std;
template<class T>
class Node
{
public:
    Node(T value, Node *next = nullptr)
    {
        this->value = value;
        this->next = next;
    }
    Node* next;
    T value;
};

template<class T>
class LinkedList
{
public:
    friend class Node<T>;
    LinkedList()
    {
        size = 0;
        first = nullptr;
        last = nullptr;
    }

    LinkedList(const LinkedList<T>& l)
    {
        T item;
        size = l.size;
        first = new Node<T>(item, nullptr);
        first = l.first;
        last = l.last;
    }

    LinkedList(T* items, int c)
    {
        this->first = nullptr;
        this->last = nullptr;
        this->size = 0;
        for (int i = 0; i < c; i++)
        {
            this->append(items[i]);
        }
    }

    LinkedList(int c)
    {
        T item;
        this->first = nullptr;
        this->last = nullptr;
        this->size = 0;
        for (int i = 0; i < c; i++)
        {
            this->append(item);
        }
    }

    T getFirst()
    {
        if (this->size == 0)
        {
            throw std::out_of_range("List is empty");
        }
        Node<T>* f = this->first;
        return f->value;
    }

    T getLast()
    {
        if (this->size == 0)
        {
            throw std::out_of_range("List is empty");
        }
        Node<T>* l = this->last;
        return l->value;
    }

    T get(int index)
    {
        if (index < 0 || index > this->size)
        {
            throw std::out_of_range("Invalid index");
        }
        Node<T>* fit = this->first;
        for (int i = 0; i < index; i++)
        {
            fit = fit->next;
        }
        return fit->value;
    }

    void pop()
    {
        T item;
        Node<T> *buff = new Node<T>(item, nullptr);
        buff = this->first;
        this->first = this->first->next;
        delete buff;
        this->size--;
    }

    LinkedList<T>* getSubList(int startIndex, int endIndex)
    {
        if (startIndex < 0 || startIndex >= this->size || endIndex < 0 || endIndex >= this->size)
        {
            throw std::out_of_range("Invalid startIndex/endIndex");
        }
        Node<T>* n = this->first;
        for (int i = 0; i < startIndex; i++)
        {
            n = n->next;
        }
        LinkedList<T>* listIndex = new LinkedList();
        for (int j = startIndex; j <= endIndex; j++)
        {
            listIndex->append(n->value);
            n = n->next;
        }
        return listIndex;
    }

    int getLength()
    {
        return this->size;
    }

    T& operator[](int index)
    {
        int c = 0;
        Node<T>* temp = this->first;
        while (temp!=nullptr)
        {
            if(c == index)
            {
                return temp->value;
            }
            temp = temp->next;
            c++;
        }
    }

    void set(int index, T item)
    {
        int c = 0;
        Node<T>* temp = this->first;
        while (temp!=nullptr)
        {
            if(c == index)
            {
                temp->value = item;
            }
            temp = temp->next;
            c++;
        }
    }

    void append(T item)
    {
        if(this->first == nullptr)
        {
            this->first = new Node<T>(item, nullptr);
            this->last = new Node<T>(item, nullptr);
        }
        else
        {
            Node<T> *temp = this->first;
            while(temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = new Node<T>(item, temp->next);
            this->last = temp->next;
        }
        this->size++;
    }

    void prepend(T item)
    {
        if (this->size == 0)
        {
            this->first = new Node<T>(item, first);
            this->last = new Node<T>(item, first);
        }
        else
        {
            this->first = new Node<T>(item, first);
        }
        this->size++;
    }

    void insertAt(int index, T item)
    {
        if (index < 0 || index > this->size)
        {
            throw std::out_of_range("Invalid index");
        }
        if (index == 0)
        {
            this->prepend(item);
        }
        if (index == this->size - 1)
        {
            this->append(item);
        }
        else
        {
            Node<T> *oldNode = this->first;
            for (int i = 0; i < index - 1; i++)
            {
                oldNode = oldNode->next;
            }
            Node<T>* newNode = new Node<T>(item, oldNode->next);
            oldNode->next = newNode;
            this->size++;
        }
    }

    void reverse()
    {
        T buff;
        LinkedList<T>* l = new LinkedList(this->getLength());
        for (int i = 0; i < (this->getLength() / 2); i++)
        {
            buff = this->get(i);
            l->set(this->get(this->getLength() - i - 1), i);
            l->set(buff, this->getLength() - i - 1);
        }
        this->first = l->first;
        this->last = l->last;
    }

    LinkedList<T>* concat(LinkedList<T> *l)
    {
        Node<T>* n = this->first;
        LinkedList<T>* concatList = new LinkedList<T>(*l);
        for (int i = 0; i < this->size; i++)
        {
            concatList->append(n->value);
            n = n->next;
        }
        return concatList;
    }

    ~LinkedList()
    {
     for (int i = 0; i < this->size; i++)
     {
         this->pop();
     }
    }


public:
    int size;
    Node<T> *first;
    Node<T> *last;
};

#endif // LINKEDLIST_H

