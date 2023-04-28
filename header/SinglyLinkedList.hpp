#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

template <class T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        mutable Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int Size;
public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    class Iterator {
    private:
        Node* node;
    public:
        Iterator(Node* node) : node(node) {}
        Iterator& operator++() {
            node = node->next;
            return *this;
        }
        Iterator operator+(int n) const {
            Node* currentNode = node;
            for (int i = 0; i < n; i++) {
                if (currentNode == nullptr) {
                    throw std::out_of_range("Index out of range");
                }
                currentNode = currentNode->next;
            }
            return Iterator(currentNode);
        }
        T& operator*() {
            return node->data;
        }
        const Node* getNode() const {
            return node;
        }
    };
    T& operator[] (int index);
    const T& operator[] (int index) const;
    void operator= (SinglyLinkedList<T> &list);
    void operator= (std::vector<T> &list);
    Iterator begin() const;
    Iterator end() const;
    T& front();
    T& back();
    void insert(const Iterator& pos, const T& data);
    void erase(const Iterator& pos);
    void resize(int newSize);
    void clear();
    void push_back(const T& data);
    void pop_back();    
    int size();
    const int size() const;
};
       

#include <SinglyLinkedList.cpp>