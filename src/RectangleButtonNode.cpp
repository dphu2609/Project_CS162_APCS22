#include <SceneGraph/RectangleButtonNode.hpp>

RectangleButtonNode::RectangleButtonNode(sf::RenderWindow &window, const std::string text , const sf::Font &font, sf::Vector2f boxSize, 
        double outlineSize, sf::Vector2f pos, sf::Color textColor, sf::Color boxColor, 
        sf::Color boxOutlineColor, sf::Color textColorHoverred, sf::Color boxColorHoverred, sf::Color boxOutlineColorHoverred
) : mWindow(window) {
    this->mButton.set(text, font, boxSize, outlineSize, pos, textColor, boxColor, boxOutlineColor, textColorHoverred, boxColorHoverred, boxOutlineColorHoverred);
}

void RectangleButtonNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    if (evn::isHoverred(this->mWindow, this->mButton.mBox)) {   
        target.draw(this->mButton.mBoxHoverred);
        target.draw(this->mButton.mTextHoverred);
    }
    else {
        target.draw(this->mButton.mBox);
        target.draw(this->mButton.mText);
    }
}

bool RectangleButtonNode::isLeftClicked() {
    return false;
}