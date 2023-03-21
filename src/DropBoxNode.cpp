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
    sf::Vector2f optionPos = pos + sf::Vector2f(0, labelOutlineSize + optionsOutlineSize);
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
    this->mOptionsContent = optionsText;
    this->mLabelContent = labelText;
    this->mIsDropped = 0;
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
        if (!this->mIsDropped) {
            this->mLabel.mText.setString(mLabelContent);
            this->mLabel.mTextHoverred.setString(mLabelContent);
            sf::Vector2f newLabelPos = this->mLabel.mBox.getPosition() + sf::Vector2f((this->mLabel.mBox.getSize().x - this->mLabel.mText.getLocalBounds().width)/2, this->mLabel.mBox.getSize().y*0.1);
            this->mLabel.mText.setPosition(newLabelPos);
            this->mLabel.mTextHoverred.setPosition(newLabelPos);
            this->mIsDropped = 1;
        }
        else this->mIsDropped = 0;
    }
    for (auto &child : this->mOptions) {
        if (evn::isLeftClicked(this->mWindow, event, child.mBox)) {
            std::string str = child.mText.getString();
            for (int i = 0; i < str.size(); i++) {
                std::transform(str.begin(), str.end(), str.begin(), ::toupper);  
            }
            this->mLabel.mText.setString(str);
            this->mLabel.mTextHoverred.setString(str);
            sf::Vector2f newLabelPos = this->mLabel.mBox.getPosition() + sf::Vector2f((this->mLabel.mBox.getSize().x - this->mLabel.mText.getLocalBounds().width)/2, this->mLabel.mBox.getSize().y*0.1);
            this->mLabel.mText.setPosition(newLabelPos);
            this->mLabel.mTextHoverred.setPosition(newLabelPos);
            this->mIsDropped = 0;
        }
    }
}

void DropBoxNode::updateCurrent(sf::Time dt) {
    if (this->mAnimationType["move"]) {
        sf::Vector2f newPos(
            this->mStartPos.x + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::cos(this->mAngleMovement*std::atan(1)*4/180),
            this->mStartPos.y + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::sin(this->mAngleMovement*std::atan(1)*4/180)
        );
        this->mLabel.setPosition(newPos);
        sf::Vector2f optionPos = newPos + sf::Vector2f(0, this->mLabel.mBox.getOutlineThickness() + this->mOptions[0].mBox.getOutlineThickness());
        for (auto &child : this->mOptions) {
            optionPos += sf::Vector2f(0, this->mLabel.mBox.getSize().y + this->mOptions[0].mBox.getOutlineThickness());
            child.setPosition(optionPos);
        }
        if (this->mCurrentPos > 0) this->mCurrentPos -= this->mMovingStep;
        else {
            this->mAnimationType["move"] = 0;
            this->mIsMoving = 0;
            this->mIsDoneMoving = 1;
        }
    }
}

void DropBoxNode::triggerMoveAnimation(sf::Time dt, double speed, double moveDistance, double angleMovement) {
    this->mCurrentPos = std::sqrt(std::sqrt(moveDistance));
    this->mMovingStep = this->mCurrentPos*dt.asSeconds()*speed;
    this->mAngleMovement = angleMovement;
    this->mStartPos = this->mLabel.mBox.getPosition();
    this->mMovingDistance = moveDistance;
    this->mAnimationType["move"] = 1;
    this->mIsMoving = 1;
    this->mIsDoneMoving = 0;
}

int DropBoxNode::getClickedIndex(sf::Event &event) {
    if (evn::isLeftClicked(mWindow, event, this->mLabel.mBox)) {
        return 0;
    }
    int index = 1;
    for (auto &child : this->mOptions) {
        if (evn::isLeftClicked(mWindow, event, child.mBox)) {
            return index;
        }
        index++;
    }
    return -1;
}