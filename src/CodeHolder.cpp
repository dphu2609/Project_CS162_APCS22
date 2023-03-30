#include <CodeHolder.hpp>


void CodeHolder::load(std::vector<int> codeID) {
    mStateActivated.resize(codeID.size());
    std::fill(mStateActivated.begin(), mStateActivated.end(), 0);
    mCodeMap.resize(Code::CodeCount);
    mCodeMap[Code::SinglyLinkedListInsert] = {
        "void insert(int index, int value, Node*& head) {",    // 0
        "    if (index == 0) {",                                // 1
        "        Node* newNode = new Node(value, nullptr);",    // 2
        "        newNode->next = head;",                    // 3
        "        head = newNode;", // 4
        "        return;",// 5
        "    }",//  6
        "    Node* cur = head;",// 7
        "    for (int i = 0; i < index - 1; i++) {",// 8
        "        cur = cur->next;",// 9
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
}

std::vector<std::string>& CodeHolder::operator[] (int id) {
    return mCodeMap[id];
}

const std::vector<std::string>& CodeHolder::operator [] (int id) const {
    return mCodeMap[id];
}