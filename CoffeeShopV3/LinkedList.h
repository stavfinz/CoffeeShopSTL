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
    LinkedList(LinkedList&& other) = delete;
    LinkedList& operator=(const LinkedList& other) = delete;
    LinkedList& operator=(LinkedList&& other) = delete;

public:
    LinkedList();
    LinkedList(const LinkedList& other);
    ~LinkedList();

    //Method adds info to the end of the list
    void add(T info);
    bool remove(Node<T>& node);
    int getSize() const { return size; }
    bool isExists(const T& data) const;
    const Node* getHead() const { return *this->head; }

    friend ostream& operator<<(ostream& os, const LinkedList& list)
    {
        const Node<T>* ptr = list.getHead();

        while (ptr != NULL)
        {
            os << "\t" << *ptr;
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
LinkedList<T>::LinkedList(const LinkedList& other)
{
    if (other.head == NULL)
    {
        this = LinkedList();
        return;
    }

    this->head = new Node<T>(other.head);
    size = 1;

    Node<T>* ptr = other.head->getNext();
    while (head != NULL)
    {
        this->add(ptr->getData());
        ptr = ptr->getNext();
    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* ptr = head

        while (ptr != NULL)
        {
            Node<T>* temp = ptr->getNext();
            delete ptr;
            ptr = temp;
        }
}

template <class T>
void LinkedList<T>::add(T info)
{
    if (head == NULL) //if our list is currently empty
    {
        head = new Node<T>; //Create new node of type T
        head->setData(info);
    }
    else //if not empty add to the end and move the tail
    {
        Node<T>* temp = new Node<T>(info);
        Node<T>* ptr = head;
        while (ptr.getNext() != NULL)
        {
            ptr = ptr.getNext();
        }
        ptr.setNext(temp);
    }
    size++;
}

template <class T>
bool LinkedList<T>::isExists(const T& data) const
{
    Node<T>& tmp = this->head();

    while (ptr != NULL)
    {
        if (tmp.getData() == data)
            return true;

        tmp = tmp.getNext();
    }
    return false;
}

template <class T>
bool LinkedList<T>::remove(Node<T>& node)
{
    Node<T>* ptr = head;
    if (ptr == node)
    {
        head = head->getNext();
        delete node;
        size--;
        return true;
    }

    while (ptr->getNext() != node && ptr != null)
    {
        ptr = ptr->getNext();
    }

    if (ptr == NULL)
        return false;

    ptr->setNext(node.getNext());
    delete node;
    size--;
    return true;
}

#endif // !__LINKEDLIST_H__
