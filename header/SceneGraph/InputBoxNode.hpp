#pragma once
#include <SceneGraph/SceneNode.hpp>

class InputBoxNode : public SceneNode {
public:
    InputBoxNode(sf::RenderWindow &window, sf::Font &font, sf::Vector2f boxSize, double outlineThickness, sf::Vector2f pos, sf::Color textColor, sf::Color boxColor, sf::Color boxOutlineColor, sf::Color cursorColor);
    // virtual int getClickedIndex(sf::Event &event);
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double movingDistance, double angleMovement);
    virtual void resetContent(std::string &str);
private:
    sf::RenderWindow &mWindow;
    InputBox mInputBox;
    bool mIsActivated;
    sf::Clock mClock;
    double mElapsedTime;
    bool mIsCursorOn;
    int mOverBoundChar;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
    virtual void handleCurrentEvent(sf::Event &event);
};