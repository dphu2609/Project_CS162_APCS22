#pragma once
#include <SceneGraph/SceneNode.hpp>
#include <DataStructure.h>

class DisplayNode : public SceneNode {
public: 
    DisplayNode(int val, sf::Font &font, double size, sf::Vector2f pos, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor);
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double distance, double angleMovement);
private:
    GraphicalNode mNode;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};