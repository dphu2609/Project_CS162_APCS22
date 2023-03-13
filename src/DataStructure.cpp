#include <DataStructure.h>

void GraphicalNode::set(std::string string, sf::Font &font, int posX, int posY, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor) {
    int size = 80;
    switch (string.size()) {
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

void GraphicalNode::setPos(sf::Vector2f pos) {
    std::string str = this->number.getString();
    switch (str.size()) {
    case 1:
        this->box.setPosition(pos);
        this->number.setPosition(pos.x + 40, pos.y + 6);
        break;
    case 2:
        this->box.setPosition(pos);
        this->number.setPosition(pos.x + 20, pos.y + 6);
        break;
    case 3:
        this->box.setPosition(pos);
        this->number.setPosition(pos.x + 8, pos.y + 14);
        break;
    case 4:
        this->box.setPosition(pos);
        this->number.setPosition(pos.x + 8, pos.y + 26);
        break;
    case 5:
        this->box.setPosition(pos);
        this->number.setPosition(pos.x + 8, pos.y + 33);
        break;
    };
}

void Pointer::set(std::string string, sf::Font &font, int posX, int posY, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor) {
    int size = 40;
    switch (string.size())
    {
    case 1:
        anm::setText(text, font, string, size, posX + 20, posY + 3, numColor);
        break;
    case 2:
        anm::setText(text, font, string, size, posX + 10, posY + 3, numColor);
        break;
    case 3:
        size = 35;
        anm::setText(text, font, string, size, posX + 4, posY + 7, numColor);
        break;
    case 4:
        size = 25;
        anm::setText(text, font, string, size, posX + 4, posY + 13, numColor);
        break;
    case 5:
        size = 20;
        anm::setText(text, font, string, size, posX + 4, posY + 16.5, numColor);
        break;
    };
    this->box.setFillColor(boxColor);
    this->box.setSize(sf::Vector2f(60, 60));
    this->box.setPosition(sf::Vector2f(posX, posY));
    this->box.setOutlineColor(boxOutlineColor);
    this->box.setOutlineThickness(10);
}






double AnimationVar::forwardVal(double startPoint, double endPoint) {
    return startPoint - std::pow(this->initialVar, 4) + endPoint;
}

double AnimationVar::backwardVal(double startPoint) {
    return startPoint + std::pow(this->initialVar, 4);
}

void AnimationVar::changeVar(double startPoint, double endPoint, double frame, double speed) {
    this->initialVar -= (std::sqrt(std::sqrt(std::abs(endPoint - startPoint)))/frame)*speed;
}


