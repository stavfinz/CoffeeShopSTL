#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <iostream>
#include "Node.h"

using namespace std;

template <class T>
class LinkedList
{
    Node<T>* head;
    int size;

private:
    LinkedList(const LinkedList& other) = delete;
    LinkedList& operator=(const LinkedList& other) = delete;
    LinkedList& operator=(LinkedList&& other) = delete;

public:
    LinkedList();
    LinkedList(LinkedList&& other);
    ~LinkedList();
    bool add(T data);       //  adds to the end of the list
    bool remove(T data);
    int getSize() const { return size; }
    bool isExists(const T& data) const;
    const Node<T>* getHead() const { return this->head; }
    T operator[](int index) const;

    friend ostream& operator<<(ostream& os, const LinkedList& list)
    {
        const Node<T>* ptr = list.getHead();
        int counter = 1;
        while (ptr != NULL)
        {
            os << "\t" << counter << ". " << *ptr << endl;
            ++counter;
            ptr = ptr->getNext();
        }
        return os;
    }
};

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    size = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* ptr = head;

    while (ptr != NULL)
    {
        Node<T>* temp = ptr->getNext();
        delete ptr;
        ptr = temp;
    }
}

template <class T>
LinkedList<T>::LinkedList(LinkedList&& other) : head(nullptr), size(other.getSize())
{
    std::swap(this->head, other.head);
}

template <class T>
bool LinkedList<T>::add(T data)
{
    if (isExists(data))
        return false;
    if (head == NULL)               //  if the list is currently empty
    {
        head = new Node<T>(data);   // create a new node of type T at the head
    }
    else                            //  if not empty add to the end
    {
        Node<T>* ptr = head;
        while (ptr->getNext() != NULL)
        {
            ptr = ptr->getNext();
        }
        ptr->setNext(new Node<T>(data));
    }
    size++;
    return true;
}

template <class T>
bool LinkedList<T>::isExists(const T& data) const
{
    Node<T>* tmp = this->head;

    while (tmp != NULL)
    {
        if (*tmp->getData() == *data)
            return true;

        tmp = tmp->getNext();
    }
    return false;
}

template <class T>
bool LinkedList<T>::remove(T otherData)
{
    Node<T>* ptr = this->head;
    if (ptr->getData() == otherData)
    {
        head = head->getNext();
        delete ptr;
        size--;
        return true;
    }

    while (ptr->getNext() != nullptr)
    {
        if (ptr->getNext()->getData() == otherData)
            break;
        ptr = ptr->getNext();
    }

    if (ptr->getNext() == NULL)
        return false;

    Node<T>* temp = ptr->getNext();
    ptr->setNext(temp->getNext());
    delete temp;
    size--;
    return true;
}

template <class T>
T LinkedList<T>::operator[](int index) const
{
    int tail = 0;
    Node<T>* tmp = this->head;

    while (tail != index && tmp != NULL)
    {
        tmp = tmp->getNext();
        tail++;
    }
    return tmp->getData();
}

#endif // !__LINKEDLIST_H__
