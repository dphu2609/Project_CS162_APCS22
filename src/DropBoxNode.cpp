#include <SceneGraph/DropBoxNode.hpp>

DropBoxNode::DropBoxNode(
        sf::RenderWindow &window, const std::string labelText, const std::vector<std::string> optionsText, const sf::Font &font, sf::Vector2f boxSize, 
        double labelOutlineSize, double optionsOutlineSize, sf::Vector2f pos, 
        sf::Color labelTextColor, sf::Color labelBoxColor, sf::Color labelBoxOutlineColor, 
        sf::Color labelTextColorHoverred, sf::Color labelBoxColorHoverred, sf::Color labelBoxOutlineColorHoverred,
        sf::Color optionsTextColor, sf::Color optionsBoxColor, sf::Color optionsBoxOutlineColor,
        sf::Color optionsTextColorHoverred, sf::Color optionsBoxColorHoverred, sf::Color optionsBoxOutlineColorHoverred
) : mWindow(window) {
    this->mLabel.set(
        labelText, font, boxSize, labelOutlineSize, pos, labelTextColor, 
        labelBoxColor, labelBoxOutlineColor, labelTextColorHoverred, labelBoxColorHoverred, labelBoxOutlineColorHoverred
    );
    sf::Vector2f optionPos = pos + sf::Vector2f(0, labelOutlineSize);
    for (auto optionText : optionsText) {
        optionPos += sf::Vector2f(0, boxSize.y + optionsOutlineSize);
        RectangleButton newOption;
        newOption.set(
            optionText, font, boxSize, optionsOutlineSize, optionPos, 
            optionsTextColor, optionsBoxColor, optionsBoxOutlineColor, 
            optionsTextColorHoverred, optionsBoxColorHoverred, optionsBoxOutlineColorHoverred
        );
        this->mOptions.push_back(newOption);
    }
}

int DropBoxNode::size() {
    return this->mOptions.size();
}

void DropBoxNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!evn::isHoverred(this->mWindow, this->mLabel.mBox)) {
        target.draw(this->mLabel.mBox);
        target.draw(this->mLabel.mText);
    } else {
        target.draw(this->mLabel.mBoxHoverred);
        target.draw(this->mLabel.mTextHoverred);
    }

    if (this->mIsDropped) {
        for (auto &option : this->mOptions) {
            if (!evn::isHoverred(this->mWindow, option.mBox)) {
                target.draw(option.mBox);
                target.draw(option.mText);
            } else {
                target.draw(option.mBoxHoverred);
                target.draw(option.mTextHoverred);
            }
        }
    }
}

void DropBoxNode::handleCurrentEvent(sf::Event &event) {
    if (evn::isLeftClicked(this->mWindow, event, this->mLabel.mBox)) {
        if (!this->mIsDropped) this->mIsDropped = 1;
        else this->mIsDropped = 0;
    }
}