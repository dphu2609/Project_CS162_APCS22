#include <Button.hpp>

void ImageButton::set(sf::Texture &originalButtonTexture, sf::Texture &hoverredButtonTexture, double width, double height, sf::Vector2f pos) {
    this->originalButton.setTexture(originalButtonTexture);
    this->hoverredButton.setTexture(hoverredButtonTexture);
    this->originalButton.setPosition(pos);
    this->hoverredButton.setPosition(pos);
    sf::Vector2f originalButtonScale(width/this->originalButton.getGlobalBounds().width, height/this->originalButton.getGlobalBounds().height);
    sf::Vector2f hoverredButtonScale(width/this->hoverredButton.getGlobalBounds().width, height/this->hoverredButton.getGlobalBounds().height);
    this->originalButton.setScale(originalButtonScale);
    this->hoverredButton.setScale(hoverredButtonScale);
}

void RectangleButton::set(const std::string text , const sf::Font &font, sf::Vector2f boxSize, 
    double outlineSize, sf::Vector2f pos, sf::Color textColor, sf::Color boxColor, 
    sf::Color boxOutlineColor, sf::Color textColorHoverred, sf::Color boxColorHoverred, sf::Color boxOutlineColorHoverred
) {
    this->mText.setFont(font);
    this->mText.setString(text);
    this->mText.setCharacterSize(boxSize.y*0.6);
    this->mText.setPosition(pos + sf::Vector2f((boxSize.x - mText.getLocalBounds().width)/2, boxSize.y*0.1));
    this->mText.setFillColor(textColor);

    this->mBox.setSize(boxSize);
    this->mBox.setPosition(pos);
    this->mBox.setFillColor(boxColor);
    this->mBox.setOutlineColor(boxOutlineColor);
    this->mBox.setOutlineThickness(outlineSize);

    this->mTextHoverred.setFont(font);
    this->mTextHoverred.setString(text);
    this->mTextHoverred.setCharacterSize(boxSize.y*0.6);
    this->mTextHoverred.setPosition(pos + sf::Vector2f((boxSize.x - mText.getLocalBounds().width)/2, boxSize.y*0.1));
    this->mTextHoverred.setFillColor(textColorHoverred);

    this->mBoxHoverred.setSize(boxSize);
    this->mBoxHoverred.setPosition(pos);
    this->mBoxHoverred.setFillColor(boxColorHoverred);
    this->mBoxHoverred.setOutlineColor(boxOutlineColorHoverred);
    this->mBoxHoverred.setOutlineThickness(outlineSize);  
}

void RectangleButton::setPosition(sf::Vector2f pos) {
    this->mBox.setPosition(pos);
    this->mBoxHoverred.setPosition(pos);
    this->mText.setPosition(pos + sf::Vector2f((mBox.getSize().x - mText.getLocalBounds().width)/2, this->mBox.getSize().y*0.1));
    this->mTextHoverred.setPosition(pos + sf::Vector2f((mBox.getSize().x - mText.getLocalBounds().width)/2, this->mBox.getSize().y*0.1));
}

void InputBox::set(sf::Font &font, sf::Vector2f boxSize, double outlineThickness, sf::Vector2f pos, sf::Color textColor, sf::Color boxColor, sf::Color boxOutlineColor, sf::Color cursorColor) {
    mContent = "";
    mInputText.setString("");
    mInputText.setFont(font);
    mInputText.setCharacterSize(boxSize.y*0.7);
    mInputText.setPosition(pos + sf::Vector2f(5, boxSize.y*0.05));
    mInputText.setFillColor(textColor);
    mBox.setSize(boxSize);
    mBox.setPosition(pos);
    mBox.setFillColor(boxColor);
    mBox.setOutlineColor(boxOutlineColor);
    mBox.setOutlineThickness(outlineThickness);
    mCursor.setSize(sf::Vector2f(3*Constant::scaleX, boxSize.y*0.9));
    mCursor.setPosition(pos + sf::Vector2f(5 + mInputText.getLocalBounds().width, boxSize.y*0.1));
    mCursor.setFillColor(cursorColor);
}

void InputBox::setPostion(sf::Vector2f pos) {
    mBox.setPosition(pos);
    mInputText.setPosition(pos + sf::Vector2f(5, mBox.getSize().y*0.05));
    mCursor.setPosition(pos + sf::Vector2f(5 + mInputText.getLocalBounds().width, mBox.getSize().y*0.05));
}