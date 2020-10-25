#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
using namespace std;

/*
T should have:
    1. operator==
    2. operator<<
    3. default copy c'tor
*/
template <class T>
class Node
{
    T data;
    Node<T>* next;

private:
    Node() = delete;
    Node& operator=(const Node<T>& other) = delete;
    Node& operator=(Node<T>&& other) = delete;

public:
    Node(T& data);
    Node(const Node<T>& other);
    ~Node();
    T getData() const { return data; }
    Node<T>* getNext() const { return next; }
    void setNext(Node<T>* node);
    void setData(T data);
    bool operator!=(const Node<T>& other) const;
    friend ostream& operator<<(ostream& os, const Node<T>& node)
    {
        os << *node.data;
        return os;
    }
};


template <class T>
Node<T>::Node(T& data)
{
    this->data = data;
    this->next = NULL;
}

template <class T>
Node<T>::Node(const Node<T>& other)
{
    this->data = other.data;
    this->next = other.next;
}

template <class T>
void Node<T>::setNext(Node<T>* node)
{
    this->next = node;
}

template <class T>
void Node<T>::setData(T data)
{
    this->data = data;
}

template <class T>
bool Node<T>::operator!=(const Node<T>& other) const
{
    return !(this->getData() == other.data);
}

template <class T>
Node<T>::~Node()
{
    delete data;
}


#endif // !__NODE_H__
