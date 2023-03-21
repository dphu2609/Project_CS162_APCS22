#pragma once
#include <SceneGraph/SceneNode.hpp>
#include <Button.hpp>

class DropBoxNode : public SceneNode {
public:
    DropBoxNode(sf::RenderWindow &window, const std::string labelText, const std::vector<std::string> optionsText, const sf::Font &font, sf::Vector2f boxSize, 
        double labelOutlineSize, double optionsOutlineSize, sf::Vector2f pos, 
        sf::Color labelTextColor, sf::Color labelBoxColor, sf::Color labelBoxOutlineColor, 
        sf::Color labelTextColorHoverred, sf::Color labelBoxColorHoverred, sf::Color labelBoxOutlineColorHoverred,
        sf::Color optionsTextColor, sf::Color optionsBoxColor, sf::Color optionsBoxOutlineColor,
        sf::Color optionsTextColorHoverred, sf::Color optionsBoxColorHoverred, sf::Color optionsBoxOutlineColorHoverred
    );
    int size();
    virtual void triggerMoveAnimation(sf::Time dt, double speed, double distance, double angleMovement);
    virtual int getClickedIndex(sf::Event &event);
private:
    sf::RenderWindow &mWindow;
    std::vector<std::string> mOptionsContent;
    RectangleButton mLabel;
    std::vector<RectangleButton> mOptions;
    std::string mLabelContent;
    bool mIsDropped;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void handleCurrentEvent(sf::Event &event);
    virtual void updateCurrent(sf::Time dt);
};
