#include <SceneGraph/CodeBlockNode.hpp>


CodeBlockNode::CodeBlockNode(
    sf::RenderWindow &window, const std::vector<std::string> &codeContent, sf::Font& font, double textSize,
    sf::Color textColor, sf::Color boxColor, sf::Color textColorActivated, sf::Color boxColorActivated
) : mCodeContent(codeContent.size()) {
    double maxWidth = 0;
    mCodeContent.resize(codeContent.size());
    mCodeContentActivated.resize(codeContent.size());
    mBox.resize(codeContent.size());
    mBoxActivated.resize(codeContent.size());
    for (int i = 0; i < codeContent.size(); i++) {
        mCodeContent[i].setFont(font);
        mCodeContent[i].setString(codeContent[i]);
        mCodeContent[i].setCharacterSize(textSize);
        mCodeContent[i].setFillColor(textColor);

        mCodeContentActivated[i].setFont(font);
        mCodeContentActivated[i].setString(codeContent[i]);
        mCodeContentActivated[i].setCharacterSize(textSize);
        mCodeContentActivated[i].setFillColor(textColorActivated);
        maxWidth = std::max(maxWidth, (double)mCodeContent[i].getLocalBounds().width);

        mLineActivated.push_back(0);
    }

    sf::Vector2f initialPos(
        sf::VideoMode::getDesktopMode().width - maxWidth - 35 - 150*Constant::scaleX, 
        sf::VideoMode::getDesktopMode().height - textSize/0.5*codeContent.size() - 70 - 50*Constant::scaleY
    );

    for (int i = 0; i < codeContent.size(); i++) {
        mBox[i].setSize(sf::Vector2f(maxWidth + 100*Constant::scaleX, textSize/0.5));
        mBox[i].setPosition(initialPos);
        mBox[i].setFillColor(boxColor);

        mBoxActivated[i].setSize(sf::Vector2f(maxWidth + 100*Constant::scaleX, textSize/0.5));
        mBoxActivated[i].setPosition(initialPos);
        mBoxActivated[i].setFillColor(boxColorActivated);

        mCodeContent[i].setPosition(initialPos + sf::Vector2f(50*Constant::scaleX, textSize/2));
        mCodeContentActivated[i].setPosition(initialPos + sf::Vector2f(50*Constant::scaleX, textSize/2));

        initialPos += sf::Vector2f(0, textSize/0.5);
    }
}

void CodeBlockNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i = 0; i < mBox.size(); i++) {
        if (mLineActivated[i]) {
            target.draw(mBoxActivated[i]);
            target.draw(mCodeContentActivated[i]);
        } else {
            target.draw(mBox[i]);
            target.draw(mCodeContent[i]);
        }
    }
}


void CodeBlockNode::updateCurrent(sf::Time dt) {
    if (this->mAnimationType["move"]) {
        sf::Vector2f newPos(
            this->mStartPos.x + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::cos(this->mAngleMovement*std::atan(1)*4/180),
            this->mStartPos.y + (-std::pow(this->mCurrentPos, 4) + this->mMovingDistance)*std::sin(this->mAngleMovement*std::atan(1)*4/180)
        );
        for (int i = 0; i < mBox.size(); i++) {
            mBox[i].setPosition(newPos);
            mBoxActivated[i].setPosition(newPos);
            mCodeContent[i].setPosition(newPos + sf::Vector2f(25, mCodeContent[i].getCharacterSize()/2));
            mCodeContentActivated[i].setPosition(newPos + sf::Vector2f(25, mCodeContentActivated[i].getCharacterSize()/2));
            newPos += sf::Vector2f(mCodeContent[i].getCharacterSize()/0.5, 0);
        }
        if (this->mCurrentPos > 0) this->mCurrentPos -= this->mMovingStep;
        else {
            this->mAnimationType["move"] = 0;
            this->mIsMoving = 0;
            this->mIsDoneMoving = 1;
        }
    }
}

void CodeBlockNode::triggerMoveAnimation(sf::Time dt, double speed, double moveDistance, double angleMovement) {
    this->mCurrentPos = std::sqrt(std::sqrt(moveDistance));
    this->mMovingStep = this->mCurrentPos*dt.asSeconds()*speed;
    this->mAngleMovement = angleMovement;
    this->mStartPos = this->mBox[0].getPosition();
    this->mMovingDistance = moveDistance;
    this->mAnimationType["move"] = 1;
    this->mIsMoving = 1;
    this->mIsDoneMoving = 0;
}

void CodeBlockNode::changeCodeBoxColor(std::vector<int> index) {
    for (auto &i : index) {
        mLineActivated[i] = 1;
    }
}

void CodeBlockNode::resetCodeBoxColor() {
    for (int i = 0; i < mLineActivated.size(); i++) {
        mLineActivated[i] = 0;
    }
}