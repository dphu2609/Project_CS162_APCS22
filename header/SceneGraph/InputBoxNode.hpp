#pragma once
#include <SceneGraph/SceneNode.hpp>

class InputBoxNode : public SceneNode {
public:
    InputBoxNode(
        sf::RenderWindow &window, sf::Font &font, sf::Vector2f boxSize, double outlineThickness, 
        sf::Vector2f pos, sf::Color textColor, sf::Color boxColor, sf::Color boxOutlineColor, sf::Color cursorColor
    );
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double movingDistance, double angleMovement);
    virtual void setContent(const std::string &str);
    virtual std::string getStringData();
    virtual bool isActivated();
    virtual std::vector<int> getIntArrayData();
private:
    sf::RenderWindow &mWindow;
    InputBox mInputBox;
    bool mIsActivated = 0;
    sf::Clock mClock;
    double mElapsedTime;
    bool mIsCursorOn = 0;
    int mOverBoundChar = 0;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
    virtual void handleCurrentEvent(sf::Event &event);
};