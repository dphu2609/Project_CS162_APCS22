#pragma once

#include <SceneGraph/SceneNode.hpp>

class CodeBlockNode : public SceneNode {
public:
    CodeBlockNode(
        sf::RenderWindow &window, const std::vector<std::string> &codeContent, sf::Font &font, double textSize,
        sf::Color textColor, sf::Color boxColor, sf::Color textColorActivated, sf::Color boxColorActivated
    );
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double distance, double angleMovement);
    virtual void changeCodeBoxColor(std::vector<int> index);
    virtual void resetCodeBoxColor();
private: 
    std::vector<sf::Text> mCodeContent;
    std::vector<sf::Text> mCodeContentActivated;
    std::vector<sf::RectangleShape> mBox;
    std::vector<sf::RectangleShape> mBoxActivated;
    std::vector<bool> mLineActivated = {};
private: 
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
};