template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    head = nullptr;
    tail = nullptr;
    Size = 0;
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template <class T>
void SinglyLinkedList<T>::insert(int index, T data) {
    if (index < 0 || index > Size) {
        throw std::out_of_range("Index out of range");
    }
    Node* newNode = new Node;
    newNode->data = data;
    if (index == 0) {
        newNode->next = head;
        head = newNode;
        if (Size == 0) {
            tail = newNode;
        }
    } else if (index == Size) {
        tail->next = newNode;
        tail = newNode;
        newNode->next = nullptr;
    } else {
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    Size++;
}

template <class T>
void SinglyLinkedList<T>::erase(int index) {
    if (index < 0 || index >= Size) {
        throw std::out_of_range("Index out of range");
    }
    if (index == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
    } else {
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        if (index == Size - 1) {
            tail = current;
        }
    }
    Size--;
}

template <class T>
int SinglyLinkedList<T>::size() {
    return Size;
}

template <class T>
int SinglyLinkedList<T>::begin() {
    return 0;
}

template <class T>
T& SinglyLinkedList<T>::operator[] (int index) {
    Node* current = head;
    for (int i = 0; i < index && current != nullptr; i++) {
        current = current->next;
    }
    if (current == nullptr) {
        throw std::out_of_range("Index out of range");
    }
    return current->data;
}

template <class T>
void SinglyLinkedList<T>::operator= (SinglyLinkedList<T> &list) {
    clear();
    Node* current = list.head;
    while (current != nullptr) {
        insert(Size, current->data);
        current = current->next;
    }
}

template <class T>
void SinglyLinkedList<T>::operator= (std::vector<T> &list) {
    clear();
    for (int i = 0; i < list.size(); i++) {
        insert(Size, list[i]);
    }
}


template <class T>
T& SinglyLinkedList<T>::back() {
    return tail->data;
}

template <class T>
T& SinglyLinkedList<T>::front() {
    return head->data;
}

template <class T>
void SinglyLinkedList<T>::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    Size = 0;
}

template <class T>
void SinglyLinkedList<T>::push_back(T data) {
    insert(Size, data);
}

template <class T>
void SinglyLinkedList<T>::pop_back() {
    erase(Size - 1);
}