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
private:
    sf::RenderWindow &mWindow;
    RectangleButton mLabel;
    std::vector<RectangleButton> mOptions;
    bool mIsDropped;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void handleCurrentEvent(sf::Event &event);
};
