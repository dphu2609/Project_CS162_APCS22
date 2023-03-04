#include "../header/DataStructure.h"

void GraphicalNode::set(std::string string, sf::Font &font, int posX, int posY, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor) {
    int size = 80;
    switch (string.size())
    {
    case 1:
        anm::setText(number, font, string, size, posX + 40, posY + 6, numColor);
        break;
    case 2:
        anm::setText(number, font, string, size, posX + 20, posY + 6, numColor);
        break;
    case 3:
        size = 70;
        anm::setText(number, font, string, size, posX + 8, posY + 14, numColor);
        break;
    case 4:
        size = 50;
        anm::setText(number, font, string, size, posX + 8, posY + 26, numColor);
        break;
    case 5:
        size = 40;
        anm::setText(number, font, string, size, posX + 8, posY + 33, numColor);
        break;
    };
    this->box.setFillColor(boxColor);
    this->box.setSize(sf::Vector2f(120, 120));
    this->box.setPosition(sf::Vector2f(posX, posY));
    this->box.setOutlineColor(boxOutlineColor);
    this->box.setOutlineThickness(10);
}