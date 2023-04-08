#include <CodeHolder.hpp>


void CodeHolder::load() {
    mStateActivated.resize(Code::CodeCount);
    std::fill(mStateActivated.begin(), mStateActivated.end(), 0);
    mCodeMap.resize(Code::CodeCount);
    mCodeMap[Code::SinglyLinkedListInsert] = {
        "void insert(int index, int value, Node*& head) {",   
        "    if (index == 0) {",                                
        "        Node* newNode = new Node(value, nullptr);",   
        "        newNode->next = head;",                    
        "        head = newNode;", 
        "        return;",
        "    }",
        "    Node* cur = head;",
        "    for (int i = 0; i < index - 1; i++) {",
        "        cur = cur->next;",
        "    }",
        "    Node* newNode = new Node(value, nullptr);",
        "    newNode->next = cur->next;",
        "    cur->next = newNode;",
        "}"
    };
    mCodeMap[Code::SinglyLinkedListDelete] = {
        "void delete(int index, Node*& head) {",
        "    if (index == 0) {",
        "        Node* temp = head;",
        "        head = head->next;",
        "        delete temp;",
        "    } else {",
        "        Node* cur = head;",
        "        for (int i = 0; i < index - 1; i++) {",
        "            cur = cur->next;",
        "        }",
        "        Node* temp = cur->next;",
        "        cur->next = temp->next;",
        "        delete temp;",
        "    }",
        "}"
    };

    mCodeMap[Code::SinglyLinkedListUpdate] = {
        "void update(int index, int value, Node* head) {",
        "    Node* cur = head;",
        "    for (int i = 0; i < index; i++) {",
        "        cur = cur->next;",
        "    }",
        "    cur->data = value;",
        "}"
    };

    mCodeMap[Code::SinglyLinkedListSearch] = {
        "Node* search(int value, Node* head) {",
        "    Node* cur = head;",
        "    while (cur != nullptr) {",
        "        if (cur->data == value) {",
        "            return cur;",
        "        }",
        "        cur = cur->next;",
        "    }",
        "    return nullptr;",
        "}"
    };

    mCodeMap[Code::DoublyLinkedListInsert] = {
        "void insert(int index, int value, Node*& head) {",
        "    if (index == 0) {",
        "        Node* newNode = new Node(value, nullptr, head);",
        "        if (head != nullptr) head->prev = newNode;",
        "        head = newNode;",
        "        return;",
        "    }",
        "    Node* cur = head;",
        "    for (int i = 0; i < index - 1; i++) {",
        "        cur = cur->next;",
        "    }",
        "    Node* newNode = new Node(value, cur, cur->next);",
        "    if (cur->next != nullptr) cur->next->prev = newNode;",
        "    cur->next = newNode;",
        "}"
    };

    mCodeMap[Code::DoublyLinkedListDelete] = {
        "void delete(Node*& head, int index) {",
        "    if (index == 0) {",
        "        Node* temp = head;",
        "        head = head->next;",
        "        head->prev = nullptr;",
        "        delete temp;",
        "    } else {",
        "        Node* cur = head;",
        "        for (int i = 0; i < index - 1; i++) {",
        "            cur = cur->next;",
        "        }",
        "        Node* temp = cur->next;",
        "        cur->next = temp->next;",
        "        if (temp->next != nullptr) temp->next->prev = cur;",
        "        delete temp;",
        "    }",
        "}"
    };

    mCodeMap[Code::DoublyLinkedListUpdate] = {
        "void update(int index, int value, Node* head) {",
        "    Node* cur = head;",
        "    for (int i = 0; i < index; i++) {",
        "        cur = cur->next;",
        "    }",
        "    cur->data = value;",
        "}"
    };

    mCodeMap[Code::DoublyLinkedListSearch] = {
        "Node* search(int value, Node* head) {",
        "    Node* cur = head;",
        "    while (cur != nullptr) {",
        "        if (cur->data == value) {",
        "            return cur;",
        "        }",
        "        cur = cur->next;",
        "    }",
        "    return nullptr;",
        "}"
    };


    mCodeMap[Code::StaticArrayInsert] = {
        "void insert(int *arr, int& size, int index, int value) {", // 0
        "    for (int i = size; i > index; i--) {",                              // 1
        "        arr[i] = arr[i-1];",                                            // 2
        "    }",                                                                 // 3
        "    arr[index] = value;",                                               // 4
        "    size++;",                                                           // 5
        "}"                                                                      // 6
    };

    mCodeMap[Code::StaticArrayDelete] = {
        "void delete(int *arr, int& size, int index) {",     // 0
        "    for (int i = index; i < size - 1; i++) {",                  // 1
        "        arr[i] = arr[i+1];",                                   // 2
        "    }",                                                         // 3
        "    size--;",                                                    // 4
        "}"                                                              // 5
    };

    mCodeMap[Code::StaticArrayUpdate] = {
        "void update(int *arr, int size, int index, int value) {",   // 0
        "    arr[index] = value;",                                    // 1
        "}"                                                            // 2
    };

    mCodeMap[Code::StaticArraySearch] = {
        "int search(int *arr, int size, int value) {",     // 0
        "    for (int i = 0; i < size; i++) {",             // 1
        "        if (arr[i] == value) {",                   // 2
        "            return i;",                            // 3
        "        }",                                         // 4
        "    }",                                             // 5
        "    return -1;",                                    // 6
        "}"                                                 // 7
    };

    mCodeMap[Code::DynamicArrayInsert] = {
        "void insert(int*& arr, int& size, int index, int value) {",     // 0
        "    int* newArr = new int[size+1];",                             // 1
        "    for (int i = 0; i < index; i++) {",                          // 2
        "        newArr[i] = arr[i];",                                    // 3
        "    }",                                                           // 4
        "    newArr[index] = value;",                                     // 5
        "    for (int i = index+1; i < size+1; i++) {",                   // 6
        "        newArr[i] = arr[i-1];",                                  // 7
        "    }",                                                           // 8
        "    size++;",                                                     // 9
        "    delete[] arr;",                                               // 10
        "    arr = newArr;",                                               // 11
        "}"                                                                // 12
    };

    mCodeMap[Code::DynamicArrayDelete] = {
        "void delete(int* arr, int& size, int index) {", // 0
        "    int* temp = new int[size - 1];", // 1
        "    for (int i = 0; i < index; i++) {", // 2
        "        temp[i] = arr[i];", // 3
        "    }", // 4
        "    for (int i = index + 1; i < size; i++) {", // 5
        "        temp[i - 1] = arr[i];", // 6
        "    }", // 7
        "    delete[] arr;", // 8
        "    arr = temp;", // 9
        "    size--;", // 10
        "}" // 11
    };

     mCodeMap[Code::DynamicArrayUpdate] = {
        "void update(int *arr, int size, int index, int value) {",   // 0
        "    arr[index] = value;",                                    // 1
        "}"                                                            // 2
    };

    mCodeMap[Code::DynamicArraySearch] = {
        "int search(int *arr, int size, int value) {",     // 0
        "    for (int i = 0; i < size; i++) {",             // 1
        "        if (arr[i] == value) {",                   // 2
        "            return i;",                            // 3
        "        }",                                         // 4
        "    }",                                             // 5
        "    return -1;",                                    // 6
        "}"                                                 // 7
    };


}

std::vector<std::string>& CodeHolder::operator[] (int id) {
    return mCodeMap[id];
}

const std::vector<std::string>& CodeHolder::operator [] (int id) const {
    return mCodeMap[id];
}