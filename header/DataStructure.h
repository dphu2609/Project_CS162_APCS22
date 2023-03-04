#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Animation.h"

class GraphicalNode {
public:
    sf::Text number;
    sf::RectangleShape box;
    void set(std::string string, sf::Font &font, int posX, int posY, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor);
};

template <typename T>
struct Node {
    T data;
    Node *next;
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public: 
    ~LinkedList();
    void create(T *arr, int n);
};