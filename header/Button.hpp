#pragma once

#include <SFML/Graphics.hpp>
#include <Constant.hpp>

class ImageButton {
public:
    sf::Sprite originalButton;
    sf::Sprite hoveredButton;
public:
    void set(
        sf::Texture &originalButtonTexture, sf::Texture &hoveredButtonTexture, 
        double width, double height, sf::Vector2f pos
    );
};

class RectangleButton {
public:
    sf::RectangleShape mBox;
    sf::Text mText; 
    sf::RectangleShape mBoxHovered;
    sf::Text mTextHovered;
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
public:
    void set(
        sf::Font &font, sf::Vector2f boxSize, double outlineThickness, 
        sf::Vector2f pos, sf::Color textColor, 
        sf::Color boxColor, sf::Color boxOutlineColor, sf::Color cursorColor
    );
    void setPostion(sf::Vector2f pos);
};

class GraphicalNode {
public:
    sf::Text number;
    sf::RectangleShape box;
    void set(
        std::string string, sf::Font &font, double size, sf::Vector2f pos, 
        sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor
    );
    void setPos(sf::Vector2f pos);
    void setColor(sf::Color textColor, sf::Color boxColor, sf::Color outlineColor);
    void setSize(double size);
    void setString(std::string string);
};