#pragma once
#include <bits/stdc++.h>

template <class T>
class SinglyLinkedList {
private: 
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    Node* tail;
    int Size;
public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    void insert(int index, T data);
    void erase(int index);
    void clear();
    void push_back(T data);
    void pop_back();
    T& back();
    T& front();
    int begin();
    int size();
    T& operator[] (int index);
    void operator= (SinglyLinkedList<T> &list);
    void operator= (std::vector<T> &list);
};

#include <SinglyLinkedList.cpp>