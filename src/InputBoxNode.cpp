#include <SceneGraph/InputBoxNode.hpp>

InputBoxNode::InputBoxNode(
    sf::RenderWindow &window, sf::Font &font, sf::Vector2f boxSize, 
    double outlineThickness, sf::Vector2f pos, sf::Color textColor, 
    sf::Color boxColor, sf::Color boxOutlineColor, sf::Color cursorColor
) : mWindow(window) {
    this->mInputBox.set(font, boxSize, outlineThickness, pos, textColor, boxColor, boxOutlineColor, cursorColor);
}

void InputBoxNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->mInputBox.mBox);
    target.draw(this->mInputBox.mInputText);
    if (this->mIsActivated && this->mIsCursorOn) {
        target.draw(this->mInputBox.mCursor);
    }
}

void InputBoxNode::updateCurrent(sf::Time dt) {
    if (this->mIsActivated) {
        if (mElapsedTime >= 0.75) {
            if (this->mIsCursorOn) this->mIsCursorOn = 0;
            else this->mIsCursorOn = 1;
            mElapsedTime = 0;
        }
        mElapsedTime += mClock.restart().asSeconds();
    }

    if (this->mAnimationType["move"]) {
        sf::Vector2f newPos(
            this->mStartPos.x + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::cos(this->mAngleMovement*std::atan(1)*4/180),
            this->mStartPos.y + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::sin(this->mAngleMovement*std::atan(1)*4/180)
        );
        this->mInputBox.setPostion(newPos);
        if (this->mCurrentPos > 0) this->mCurrentPos -= this->mMovingStep;
        else {
            this->mAnimationType["move"] = 0;
            this->mIsMoving = 0;
            this->mIsDoneMoving = 1;
        }
    }
}

void InputBoxNode::handleCurrentEvent(sf::Event &event) {
    if (evn::isLeftClicked(mWindow, event, this->mInputBox.mBox)) {
        this->mIsActivated = 1;
        this->mIsCursorOn = 1;
        mElapsedTime = 0;
        mClock.restart();
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        this->mIsActivated = 0;
    }
    if (this->mIsActivated) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128 && event.text.unicode != 8 && this->mInputBox.mContent.size() < 100) {
                this->mInputBox.mContent += static_cast<char>(event.text.unicode);
                if (this->mInputBox.mInputText.getLocalBounds().width >= this->mInputBox.mBox.getSize().x - this->mInputBox.mInputText.getCharacterSize()*1) {
                    mOverBoundChar++;
                    std::string str = "";
                    for (int i = mOverBoundChar; i < this->mInputBox.mContent.size(); i++) {
                        str += this->mInputBox.mContent[i];
                    }
                    this->mInputBox.mInputText.setString(str);
                }
                else this->mInputBox.mInputText.setString(this->mInputBox.mContent);
                mInputBox.mCursor.setPosition(mInputBox.mBox.getPosition() + sf::Vector2f(7 + mInputBox.mInputText.getLocalBounds().width, mInputBox.mBox.getSize().y*0.05));
                this->mIsCursorOn = 1;
                mElapsedTime = 0;
            }
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Backspace && this->mInputBox.mInputText.getString().getSize() > 0) {
                this->mInputBox.mContent.erase(this->mInputBox.mContent.size() - 1);
                if (this->mInputBox.mInputText.getLocalBounds().width >= this->mInputBox.mBox.getSize().x - this->mInputBox.mInputText.getCharacterSize()*1.5) {
                    if (mOverBoundChar > 0) mOverBoundChar--;
                    std::string str = "";
                    for (int i = mOverBoundChar; i < this->mInputBox.mContent.size(); i++) {
                        str += this->mInputBox.mContent[i];
                    }
                    this->mInputBox.mInputText.setString(str);
                }
                else this->mInputBox.mInputText.setString(this->mInputBox.mContent);
                mInputBox.mCursor.setPosition(mInputBox.mBox.getPosition() + sf::Vector2f(7 + mInputBox.mInputText.getLocalBounds().width, mInputBox.mBox.getSize().y*0.05));
                this->mIsCursorOn = 1;
                mElapsedTime = 0;
            }
        }
    }
}

void InputBoxNode::triggerMoveAnimation(sf::Time dt, double speed, double moveDistance, double angleMovement) {
    this->mCurrentPos = std::sqrt(std::sqrt(moveDistance));
    this->mMovingStep = this->mCurrentPos*dt.asSeconds()*speed;
    this->mAngleMovement = angleMovement;
    this->mStartPos = this->mInputBox.mBox.getPosition();
    this->mMovingDistance = moveDistance;
    this->mAnimationType["move"] = 1;
    this->mIsMoving = 1;
    this->mIsDoneMoving = 0;
}

void InputBoxNode::setContent(const std::string &str) {
    std::string temp = "";
    this->mInputBox.mContent = str;
    mOverBoundChar = 0;
    for (int i = 0; i < str.size(); i++) {
        temp += str[i];
        if ((this->mInputBox.mInputText.getLocalBounds().width >= this->mInputBox.mBox.getSize().x - this->mInputBox.mInputText.getCharacterSize()*1)) {
            std::string string = "";
            mOverBoundChar++;
            for (int i = mOverBoundChar; i < this->mInputBox.mContent.size(); i++) {
                string += this->mInputBox.mContent[i];
            }
            this->mInputBox.mInputText.setString(str);
        }
        else {
            this->mInputBox.mInputText.setString(temp);
        }
    }
    mInputBox.mCursor.setPosition(mInputBox.mBox.getPosition() + sf::Vector2f(7 + mInputBox.mInputText.getLocalBounds().width, mInputBox.mBox.getSize().y*0.05));
}

std::string InputBoxNode::getStringData() {
    return this->mInputBox.mContent;
}

bool InputBoxNode::isActivated() {
    return this->mIsActivated;
}

std::vector<int> InputBoxNode::getIntArrayData() {
    if (mInputBox.mContent.size() == 0) return {};
    std::vector<int> result = {};
    std::string temp = "";
    bool isValid = 1;
    for (int i = 0; i < this->mInputBox.mContent.size(); i++) {
        if ((mInputBox.mContent[i] >= '0' && mInputBox.mContent[i] <= '9') || (mInputBox.mContent[i] == '-' && temp.size() == 0)) {
            temp += mInputBox.mContent[i];
            if (i == mInputBox.mContent.size() - 1 && !(temp.size() == 1 && temp[0] == '-') && isValid) {
                result.push_back(std::stoi(temp));
            }
        } else if (mInputBox.mContent[i] == ',') {
            if (isValid && !(temp.size() == 1 && temp[0] == '-')) result.push_back(std::stoi(temp));
            temp = "";
            isValid = 1;
        } else if (mInputBox.mContent[i] != ' ' || (temp.size() == 1 && temp[0] == '-')) {
            isValid = 0;
        }
    }
    return result;
}