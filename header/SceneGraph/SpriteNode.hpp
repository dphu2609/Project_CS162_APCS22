#pragma once
#include <SceneGraph/SceneNode.hpp>

class SpriteNode : public SceneNode {
public:
    SpriteNode(sf::Texture &texture, sf::Vector2f size, sf::Vector2f pos, double rotation);
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double distance, double angleMovement);
    virtual void triggerRotateAnimation(sf::Time dt, double speed, double rotateDistance);
    virtual void triggerScaleAnimation(sf::Time dt, double lengthSpeed, double scalingLengthDistance, double widthSpeed, double scalingWidthDistance);
private:
    sf::Sprite mSprite;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};