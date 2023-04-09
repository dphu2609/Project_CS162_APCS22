#pragma once

#include <bits/stdc++.h>

namespace Code {
    enum ID {
        SinglyLinkedListInsert,
        SinglyLinkedListDelete,
        SinglyLinkedListUpdate,
        SinglyLinkedListSearch,
        DoublyLinkedListInsert,
        DoublyLinkedListDelete,
        DoublyLinkedListUpdate,
        DoublyLinkedListSearch,
        CircularLinkedListInsert,
        CircularLinkedListInsertHead,
        CircularLinkedListDelete,
        CircularLinkedListDeleteHead,
        CircularLinkedListUpdate,
        CircularLinkedListSearch,
        StackPush,
        StackPop,
        QueuePush,
        QueuePop,
        StaticArrayInsert,
        StaticArrayDelete,
        StaticArrayUpdate,
        StaticArraySearch,
        DynamicArrayInsert,
        DynamicArrayDelete,
        DynamicArrayUpdate,
        DynamicArraySearch,
        CodeCount
    };
};


class CodeHolder {
public:
    void load();
    std::vector<std::string>& operator [] (int id);
    const std::vector<std::string>& operator [] (int id) const;
    std::vector<bool> mStateActivated = {};
private:
    std::vector<std::vector<std::string>> mCodeMap; 
};