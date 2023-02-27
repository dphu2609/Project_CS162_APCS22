#include "../header/LinkedList.h"

template <typename T> 
LinkedList<T> :: ~LinkedList() {
    while (head) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void LinkedList<T> :: insertTail(T data) {
    if (head == nullptr) {
        head = new Node;
        head->data = data;
        head->next = nullptr;
        tail = head;
    }
    else {
        tail->next = new Node;
        tail = tail->next;
        tail->data = data;
        tail->next = nullptr;
    }
}

template <typename T>
void LinkedList<T> :: display() {
    Node *temp = head;
    while (temp) {
        std::cout << temp->data << ' ';
        temp = temp->next;
    }
    std::cout << std::endl;
}

template class LinkedList<int>;
template class LinkedList<float>;
template class LinkedList<char>;