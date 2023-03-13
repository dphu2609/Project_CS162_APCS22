#include <Animation.h>

bool anm::isHover(sf::Text text, sf::Vector2i pos) {
    sf::FloatRect textBounds = text.getGlobalBounds();
    sf::Vector2f startPoint(textBounds.left, textBounds.top);
    sf::Vector2f endPoint(textBounds.left + textBounds.width, textBounds.top + textBounds.height);
    return pos.x >= textBounds.left && pos.x <= textBounds.left + textBounds.width && pos.y >= textBounds.top && pos.y <= textBounds.top + textBounds.height;
}

void anm::setText(sf::Text &text, sf::Font &font, std::string string, int size, int posX, int posY, sf::Color color) {
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(size);
    text.setPosition(posX, posY);
    text.setFillColor(color);
}

void anm::hoverText(sf::Text &text, sf::Vector2i pos, sf::Color newColor, sf::Color orginalColor) {
    if (anm::isHover(text, pos)) {
        text.setFillColor(newColor);
    } else text.setFillColor(orginalColor);
}

//InputBox

anm::InputBox::InputBox(sf::Font &font, int textSize, sf::Color textColor, float posX, float posY, float boxLength, sf::Color boxColor, sf::Color boxOutlineColor, int outLineThickness) {
    content = "";
    inputText.setString("");
    inputText.setFont(font);
    inputText.setCharacterSize(textSize);
    inputText.setPosition(posX, posY);
    inputText.setFillColor(textColor);
    inputBox.setSize(sf::Vector2f(boxLength, textSize + 10));
    inputBox.setPosition(posX, posY);
    inputBox.setFillColor(boxColor);
    inputBox.setOutlineColor(boxOutlineColor);
    inputBox.setOutlineThickness(outLineThickness);
}

void anm::InputBox::type(sf::Event &event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128 && event.text.unicode != 8) {
            content += static_cast<char>(event.text.unicode);
            inputText.setString(content);
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Backspace && inputText.getString().getSize() > 0) {
            content.erase(content.size() - 1);
            inputText.setString(content);
        }
    }
}

//-----------------------------------------------------