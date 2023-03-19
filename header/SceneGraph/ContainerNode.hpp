#pragma once
#include <SceneGraph/SceneNode.hpp>

class ContainerNode : public SceneNode {
public:
    ContainerNode(sf::RenderWindow &window, sf::Vector2f size, double outlineSize, sf::Vector2f pos, sf::Color boxColor, sf::Color boxOutlineColor);
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double movingDistance, double angleMovement);
private:
    sf::RenderWindow &mWindow;
    sf::RectangleShape mBox;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};