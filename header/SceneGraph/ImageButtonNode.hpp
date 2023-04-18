#pragma once
#include <SceneGraph/SceneNode.hpp>

class ImageButtonNode : public SceneNode {
public:
    ImageButtonNode(
        sf::RenderWindow &window, sf::Texture &originalButtonTexture, 
        sf::Texture &hoveredButtonTexture, sf::Vector2f size, sf::Vector2f pos
    );
    virtual int getClickedIndex(sf::Event &event);
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double movingDistance, double angleMovement);
private:
    ImageButton mButton;
    sf::RenderWindow &mWindow;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};
