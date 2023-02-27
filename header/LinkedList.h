#pragma once

#include <iostream>

template <typename T> 
class LinkedList {
private:
    struct Node {
        T data;
        Node *next;
    };
    Node* head;
    Node* tail;

public: 
    ~LinkedList();
    void insertTail(T data);
    void display();
};