#include <SceneGraph/DisplayNode.hpp>

DisplayNode::DisplayNode(int val, sf::Font &font, double size, sf::Vector2f pos, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor) {
    std::string string = std::to_string(val);
    this->mNode.set(string, font, size, pos, numColor, boxColor, boxOutlineColor);
    this->mLabel.setFont(font);
    this->mLabel.setString("");
    this->mLabel.setCharacterSize(size*0.5);
    this->mLabel.setPosition(this->mNode.box.getPosition() + sf::Vector2f(this->mNode.box.getSize().x*0.5, this->mNode.box.getSize().y + 20) - sf::Vector2f(this->mLabel.getLocalBounds().width/2 + size*0.05, 0));
    this->mLabel.setFillColor(sf::Color(250, 152, 132, 255));
}

DisplayNode::DisplayNode(int val, sf::Font &font, double size, std::string label, double labelSize, sf::Vector2f pos, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor) {
    std::string string = std::to_string(val);
    this->mNode.set(string, font, size, pos, numColor, boxColor, boxOutlineColor);
    this->mLabel.setFont(font);
    this->mLabel.setString(label);
    this->mLabel.setCharacterSize(labelSize);
    this->mLabel.setPosition(this->mNode.box.getPosition() + sf::Vector2f(this->mNode.box.getSize().x*0.5, this->mNode.box.getSize().y + 20) - sf::Vector2f(this->mLabel.getLocalBounds().width/2 + size*0.05, 0));
    this->mLabel.setFillColor(sf::Color(250, 152, 132, 255));
}

void DisplayNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mNode.box);
    target.draw(mNode.number);
    target.draw(mLabel);
}

void DisplayNode::updateCurrent(sf::Time dt) {
    if (this->mAnimationType["move"]) {
        sf::Vector2f newPos(
            this->mStartPos.x + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::cos(this->mAngleMovement*std::atan(1)*4/180),
            this->mStartPos.y + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::sin(this->mAngleMovement*std::atan(1)*4/180)
        );
        this->mNode.setPos(newPos);
        this->mLabel.setPosition(this->mNode.box.getPosition() + sf::Vector2f(this->mNode.box.getSize().x*0.5, this->mNode.box.getSize().y + 20) - sf::Vector2f(this->mLabel.getLocalBounds().width/2 + this->mNode.box.getOutlineThickness(), 0));
        if (this->mCurrentPos > 0) this->mCurrentPos -= this->mMovingStep;
        else {
            this->mAnimationType["move"] = 0;
            this->mIsMoving = 0;
            this->mIsDoneMoving = 1;
        }
    }

    if (this->mAnimationType["scale"]) {
        double newSize;
        if (this->mScalingLengthDistance >= 0) 
            newSize = this->mStartScale.x - std::pow(this->mCurrentLengthScale, 4) + this->mScalingLengthDistance;
        else    
            newSize = this->mStartScale.x + std::pow(this->mCurrentLengthScale, 4) + this->mScalingLengthDistance;
        this->mNode.setSize(newSize);
        this->mLabel.setCharacterSize(mNode.box.getSize().x*5/12);
        this->mLabel.setPosition(this->mNode.box.getPosition() + sf::Vector2f(this->mNode.box.getSize().x*0.5, this->mNode.box.getSize().y + 20) - sf::Vector2f(this->mLabel.getLocalBounds().width/2 + this->mNode.box.getOutlineThickness(), 0));
        if (this->mCurrentLengthScale > 0) this->mCurrentLengthScale -= this->mScalingLengthStep;
        else {
            this->mAnimationType["scale"] = 0;
            this->mIsScaling = 0;
            this->mIsDoneScaling = 1;
        }
    }

    if (this->mAnimationType["color"]) {
        mStartTime += mClock.restart().asSeconds();
        if (mStartTime > mTimeChange) {
            this->mNode.setColor(mTextColorAfterChange, mBoxColorAfterChange, mOutlineColorAfterChange);
            this->mIsColoring = 0;
            this->mIsDoneColoring = 1;
            this->mStartTime = 0;
            this->mAnimationType["color"] = 0;
        }
    } else {
        mClock.restart();
    }
}

void DisplayNode::triggerMoveAnimation(sf::Time dt, double speed, double moveDistance, double angleMovement) {
    this->mCurrentPos = std::sqrt(std::sqrt(moveDistance));
    this->mMovingStep = this->mCurrentPos*dt.asSeconds()*speed;
    this->mAngleMovement = angleMovement;
    this->mStartPos = this->mNode.box.getPosition();
    this->mMovingDistance = moveDistance;
    this->mAnimationType["move"] = 1;
    this->mIsMoving = 1;
    this->mIsDoneMoving = 0;
}

void DisplayNode::triggerScaleAnimation(sf::Time dt, double lengthSpeed, double scalingLengthDistance, double widthSpeed, double scalingWidthDistance) {
    this->mCurrentLengthScale = std::sqrt(std::sqrt(std::abs(scalingLengthDistance)));
    this->mScalingLengthStep = this->mCurrentLengthScale*dt.asSeconds()*lengthSpeed;
    this->mScalingLengthDistance = scalingLengthDistance;

    this->mCurrentWidthScale = std::sqrt(std::sqrt(std::abs(scalingWidthDistance)));
    this->mScalingWidthStep = this->mCurrentWidthScale*dt.asSeconds()*widthSpeed;
    this->mScalingWidthDistance = scalingWidthDistance;

    sf::Vector2f startScale = this->mNode.box.getSize();
    startScale.x /= 1.2;
    this->mStartScale = startScale;
    this->mAnimationType["scale"] = 1;
    this->mIsScaling = 1;
    this->mIsDoneScaling = 0;
}

void DisplayNode::triggerColorAnimation(
    sf::Time dt, double speed, 
    sf::Color textColorWhenChange, sf::Color boxColorWhenChange, sf::Color outlineColorWhenChange, 
    sf::Color textColorAfterChange, sf::Color boxColorAfterChange, sf::Color outlineColorAfterChange
) {
    this->mTextColorWhenChange = textColorWhenChange;
    this->mTextColorAfterChange = textColorAfterChange;
    this->mBoxColorWhenChange = boxColorWhenChange;
    this->mBoxColorAfterChange = boxColorAfterChange;
    this->mOutlineColorWhenChange = outlineColorWhenChange;
    this->mOutlineColorAfterChange = outlineColorAfterChange;
    this->mTimeChange = 0.75/speed;
    this->mIsColoring = 1;
    this->mIsDoneColoring = 0;
    this->mAnimationType["color"] = 1;
    this->mNode.setColor(textColorWhenChange, boxColorWhenChange, outlineColorWhenChange);
}

void DisplayNode::triggerChangeContent(std::string string) {
    this->mNode.setString(string);
}

std::string DisplayNode::getStringData() {
    std::string str = this->mNode.number.getString();
    return str;
}

void DisplayNode::setLabel(std::string text) {
    this->mLabel.setString(text);
    this->mLabel.setPosition(this->mNode.box.getPosition() + sf::Vector2f(this->mNode.box.getSize().x*0.5, this->mNode.box.getSize().y + 20) - sf::Vector2f(this->mLabel.getLocalBounds().width/2 + this->mNode.box.getOutlineThickness(), 0));
}