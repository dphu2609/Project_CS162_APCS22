#include "../header/DataStructure.h"

template <typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void LinkedList<T>::create(T *arr, int n) {
    Node<T>* newNode = new Node<T>;
    newNode->data = arr[0];
    newNode->next = nullptr;
    head = newNode;
    tail = newNode;
    for (int i = 0; i < n; i++) {
        if (i) {
            newNode = new Node<T>;
            newNode->data = arr[i];
            newNode->next = nullptr;
            tail->next = newNode;
            tail = newNode;
        }
    }
    size = n;
}

template class LinkedList<int>;
template class LinkedList<float>;
template class LinkedList<char>;