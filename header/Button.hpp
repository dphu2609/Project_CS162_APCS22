#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
};

class ImageButton : public Button {
public:
    sf::Sprite originalButton;
    sf::Sprite hoverredButton;
public:
    void set(sf::Texture &originalButtonTexture, sf::Texture &hoverredButtonTexture, double width, double height, sf::Vector2f pos);
};

class RectangleButton :  public Button {
public:
    sf::RectangleShape mBox;
    sf::Text mText; 
    sf::RectangleShape mBoxHoverred;
    sf::Text mTextHoverred;
public:
    void set(const std::string text , const sf::Font &font, sf::Vector2f boxSize, 
        double outlineSize, sf::Vector2f pos, sf::Color textColor, sf::Color boxColor, 
        sf::Color boxOutlineColor, sf::Color textColorHoverred, sf::Color boxColorHoverred, sf::Color boxOutlineColorHoverred
    );
    void setPosition(sf::Vector2f pos);
};

class InputBox {
public:
    std::string mContent = "";
    sf::Text mInputText;
    sf::RectangleShape mBox;
    sf::RectangleShape mCursor;
    void set(sf::Font &font, sf::Vector2f boxSize, double outlineThickness, sf::Vector2f pos, sf::Color textColor, sf::Color boxColor, sf::Color boxOutlineColor, sf::Color cursorColor);
    void setPostion(sf::Vector2f pos);
};