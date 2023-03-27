#pragma once
#include <SceneGraph/SceneNode.hpp>
#include <DataStructure.h>

class DisplayNode : public SceneNode {
public: 
    DisplayNode(int val, sf::Font &font, double size, sf::Vector2f pos, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor);
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double distance, double angleMovement);
    virtual void triggerColorAnimation(
        sf::Time dt, double speed, 
        sf::Color textColorWhenChange, sf::Color boxColorWhenChange, sf::Color outlineColorWhenChange, 
        sf::Color textColorAfterChange, sf::Color boxColorAfterChange, sf::Color outlineColorAfterChange
    );
    virtual void triggerScaleAnimation(sf::Time dt, double lengthSpeed, double scalingLengthDistance, double widthSpeed, double scalingWidthDistance);
    virtual void triggerChangeContent(std::string string);
    virtual std::string getStringData();
private:
    GraphicalNode mNode;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};