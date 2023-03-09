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

ImageButton::ImageButton(std::string originalButtonImagePath, std::string hoverredButtonImagePath, double width, double height, sf::Vector2f pos) {
    if (!this->originalButtonTexture.loadFromFile(originalButtonImagePath)) {
        std::cout << "Error when accessing " << originalButtonImagePath << std::endl;
    }
    if (!this->hoverredButtonTexture.loadFromFile(hoverredButtonImagePath)) {
        std::cout << "Error when accessing " << hoverredButtonImagePath << std::endl;
    }
    this->originalButton.setTexture(this->originalButtonTexture);
    this->hoverredButton.setTexture(this->hoverredButtonTexture);
    this->originalButton.setPosition(pos);
    this->hoverredButton.setPosition(pos);
    sf::Vector2f originalButtonScale(width/this->originalButton.getGlobalBounds().width, height/this->originalButton.getGlobalBounds().height);
    sf::Vector2f hoverredButtonScale(width/this->hoverredButton.getGlobalBounds().width, height/this->hoverredButton.getGlobalBounds().height);
    this->originalButton.setScale(originalButtonScale);
    this->hoverredButton.setScale(hoverredButtonScale);
}

void ImageButton::activate(sf::RenderWindow &window) {
    sf::Vector2i localPosition(sf::Mouse::getPosition(window));
    sf::FloatRect buttonBounds = this->originalButton.getGlobalBounds();
    sf::Vector2f startPoint(buttonBounds.left, buttonBounds.top);
    sf::Vector2f endPoint(buttonBounds.left + buttonBounds.width, buttonBounds.top + buttonBounds.height);
    if (
        localPosition.x >= buttonBounds.left && 
        localPosition.x <= buttonBounds.left + buttonBounds.width && 
        localPosition.y >= buttonBounds.top && 
        localPosition.y <= buttonBounds.top + buttonBounds.height
    ) window.draw(this->hoverredButton);
    else window.draw(this->originalButton);
}

bool ImageButton::isClicked(sf::RenderWindow &window) {
    sf::Vector2i localPosition(sf::Mouse::getPosition(window));
    sf::FloatRect buttonBounds = this->originalButton.getGlobalBounds();
    sf::Vector2f startPoint(buttonBounds.left, buttonBounds.top);
    sf::Vector2f endPoint(buttonBounds.left + buttonBounds.width, buttonBounds.top + buttonBounds.height);
    return (
        localPosition.x >= buttonBounds.left && 
        localPosition.x <= buttonBounds.left + buttonBounds.width && 
        localPosition.y >= buttonBounds.top && 
        localPosition.y <= buttonBounds.top + buttonBounds.height && 
        sf::Mouse::isButtonPressed(sf::Mouse::Left)
    );
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


