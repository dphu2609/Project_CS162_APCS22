#include <Button.hpp>

void ImageButton::set(sf::Texture &originalButtonTexture, sf::Texture &hoverredButtonTexture, double width, double height, sf::Vector2f pos) {
    this->originalButton.setTexture(originalButtonTexture);
    this->hoverredButton.setTexture(hoverredButtonTexture);
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