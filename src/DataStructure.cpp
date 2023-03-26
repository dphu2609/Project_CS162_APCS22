#include <DataStructure.h>

void GraphicalNode::set(std::string string, sf::Font &font, double size , sf::Vector2f pos, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor) {
    switch (string.size()) {
    case 1:
        anm::setText(number, font, string, size*0.8, pos.x + size*0.4, pos.y + size*0.06, numColor);
        break;
    case 2:
        anm::setText(number, font, string, size*0.8, pos.x + size*0.2, pos.y + size*0.06, numColor);
        break;
    case 3:
        anm::setText(number, font, string, size*0.7, pos.x + size*0.08, pos.y + size*0.14, numColor);
        break;
    case 4:
        anm::setText(number, font, string, size*0.5, pos.x + size*0.08, pos.y + size*0.26, numColor);
        break;
    case 5:
        anm::setText(number, font, string, size*0.4, pos.x + size*0.08, pos.y + size*0.33, numColor);
        break;
    };
    this->box.setFillColor(boxColor);
    this->box.setSize(sf::Vector2f(size*1.2, size*1.2));
    this->box.setPosition(pos);
    this->box.setOutlineColor(boxOutlineColor);
    this->box.setOutlineThickness(0.1*size);
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

void GraphicalNode::setColor(sf::Color textColor, sf::Color boxColor, sf::Color outlineColor) {
    this->number.setFillColor(textColor);
    this->box.setFillColor(boxColor);
    this->box.setOutlineColor(outlineColor);
}

void GraphicalNode::setSize(double size) {
    std::string string = this->number.getString();
    double oldSize = this->box.getSize().x/1.2;
    sf::Vector2f newPos = this->box.getPosition() + sf::Vector2f((oldSize - size)/2, (oldSize - size)/2);
    this->box.setSize(sf::Vector2f(size*1.2, size*1.2));
    this->box.setPosition(newPos);
    this->box.setOutlineThickness(size*0.1);
    double textSize;
    switch (string.size()) {
    case 1:
        textSize = size*0.8;
        newPos.x += size*0.4;
        newPos.y += size*0.06;  
        break;
    case 2:
        textSize = size*0.8;
        newPos.x += size*0.2;
        newPos.y += size*0.06;
        break;
    case 3:
        textSize = size*0.7;
        newPos.x += size*0.08;
        newPos.y += size*0.14;
        break;
    case 4:
        textSize = size*0.5;
        newPos.x += size*0.08;
        newPos.y += size*0.26;
        break;
    case 5:
        textSize = size*0.4;
        newPos.x += size*0.08;
        newPos.y += size*0.33;
        break;
    };
    this->number.setPosition(newPos);
    this->number.setCharacterSize(textSize);
}


