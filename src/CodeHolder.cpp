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
        "        if (cur == nullptr) {",
        "            return;",
        "        }",
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

    mCodeMap[Code::StaticArrayInsert] = {
        "void insert(int *arr, int& size, int index, int value) {", // 0
        "    for (int i = size; i > index; i--) {",                              // 1
        "        arr[i] = arr[i-1];",                                            // 2
        "    }",                                                                 // 3
        "    arr[index] = value;",                                               // 4
        "    size++;",                                                           // 5
        "}"                                                                      // 6
    };

}

std::vector<std::string>& CodeHolder::operator[] (int id) {
    return mCodeMap[id];
}

const std::vector<std::string>& CodeHolder::operator [] (int id) const {
    return mCodeMap[id];
}