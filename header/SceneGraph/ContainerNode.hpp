#pragma once
#include <SceneGraph/SceneNode.hpp>

class ContainerNode : public SceneNode {
public:
    ContainerNode(
        sf::RenderWindow &window, sf::Vector2f size, double outlineSize, sf::Vector2f pos, 
        sf::Color boxColor, sf::Color boxOutlineColor
    );
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double movingDistance, double angleMovement);
    virtual void triggerScaleAnimation(
        sf::Time dt, double lengthSpeed, double scalingLengthDistance, 
        double widthSpeed, double scalingWidthDistance
    );
    virtual void triggerRotateAnimation(sf::Time dt, double speed, double rotatingDistance);
    virtual void triggerColorAnimation(
        sf::Time dt, double speed, 
        sf::Color textColorWhenChange, sf::Color boxColorWhenChange, sf::Color outlineColorWhenChange, 
        sf::Color textColorAfterChange, sf::Color boxColorAfterChange, sf::Color outlineColorAfterChange
    );
private:
    sf::RenderWindow &mWindow;
    sf::RectangleShape mBox;
    sf::Text mLabel;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};