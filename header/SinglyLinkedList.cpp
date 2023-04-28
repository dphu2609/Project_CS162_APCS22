template <class T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), tail(nullptr), Size(0) {}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}

template <class T>
void SinglyLinkedList<T>::insert(const Iterator& pos, const T& data) {
    Node* newNode = new Node(data);
    if (pos.getNode() == head) {
        newNode->next = head;
        head = newNode;
        if (Size == 0) {
            tail = newNode;
        }
    } else if (pos.getNode() == nullptr) {
        tail->next = newNode;
        tail = newNode;
        newNode->next = nullptr;    
    } else {
        Node* current = head;
        while (current->next != pos.getNode()) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    Size++;
}

template <class T>
 void SinglyLinkedList<T>::erase(const Iterator& pos) {
    if (pos.getNode() == nullptr) {
        throw std::out_of_range("Invalid iterator");
    }
    if (pos.getNode() == head) {
        Node* oldNode = head;
        head = head->next;
        delete oldNode;
        if (Size == 1) {
            tail = nullptr;
        }
    } else {
        Node* current = head;
        while (current->next != pos.getNode()) {
            current = current->next;
        }
        current->next = pos.getNode()->next;
        if (pos.getNode() == tail) {
            tail = current;
        }
        delete pos.getNode();
    }
    Size--;
}

template <class T>
int SinglyLinkedList<T>::size() {
    return Size;
}

template <class T>
const int SinglyLinkedList<T>::size() const {
    return Size;
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
const T& SinglyLinkedList<T>::operator[] (int index) const {
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
        insert(nullptr, current->data);
        current = current->next;
    }
}

template <class T>
void SinglyLinkedList<T>::operator= (std::vector<T> &list) {
    clear();
    for (int i = 0; i < list.size(); i++) {
        insert(nullptr, list[i]);
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
    while (head != nullptr) {
        Node* oldNode = head;
        head = head->next;
        delete oldNode;
    }
    tail = nullptr;
    Size = 0;
}

template <class T>
void SinglyLinkedList<T>::push_back(const T& data) {
    insert(nullptr, data);
}

template <typename T>
void SinglyLinkedList<T>::pop_back() {
    erase(tail);
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin() const {
    return Iterator(head);
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end() const {
    return Iterator(nullptr);
}

template <class T>
void SinglyLinkedList<T>::resize(int newSize) {
    if (newSize < 0) {
        throw std::invalid_argument("Invalid size");
    }
    if (newSize == 0) {
        clear();
        return;
    }
    if (newSize < Size) {
        Node* current = head;
        for (int i = 0; i < newSize - 1; i++) {
            current = current->next;
        }
        tail = current;
        Node* oldNode = current->next;
        current->next = nullptr;
        while (oldNode != nullptr) {
            Node* nextNode = oldNode->next;
            delete oldNode;
            oldNode = nextNode;
        }
    } else {
        Node* current = head;
        for (int i = 0; i < Size - 1; i++) {
            current = current->next;
        }
        for (int i = 0; i < newSize - Size; i++) {
            Node* newNode = new Node(T());
            current->next = newNode;
            current = newNode;
        }
        tail = current;
    }
    Size = newSize;
}