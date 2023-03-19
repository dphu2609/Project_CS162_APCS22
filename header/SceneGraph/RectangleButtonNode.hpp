#pragma once
#include <SceneGraph/SceneNode.hpp>

class RectangleButtonNode : public SceneNode {
public:
    RectangleButtonNode(sf::RenderWindow &window, const std::string text , const sf::Font &font, sf::Vector2f boxSize, 
        double outlineSize, sf::Vector2f pos, sf::Color textColor, sf::Color boxColor, 
        sf::Color boxOutlineColor, sf::Color textColorHoverred, sf::Color boxColorHoverred, sf::Color boxOutlineColorHoverred
    );
    virtual bool isLeftClicked();
private:
    RectangleButton mButton;
    sf::RenderWindow &mWindow;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
};