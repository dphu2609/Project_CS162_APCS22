#include <Button.hpp>

void ImageButton::set(sf::Texture &originalButtonTexture, sf::Texture &hoveredButtonTexture, double width, double height, sf::Vector2f pos) {
    this->originalButton.setTexture(originalButtonTexture);
    this->hoveredButton.setTexture(hoveredButtonTexture);
    this->originalButton.setPosition(pos);
    this->hoveredButton.setPosition(pos);
    sf::Vector2f originalButtonScale(width/this->originalButton.getGlobalBounds().width, height/this->originalButton.getGlobalBounds().height);
    sf::Vector2f hoveredButtonScale(width/this->hoveredButton.getGlobalBounds().width, height/this->hoveredButton.getGlobalBounds().height);
    this->originalButton.setScale(originalButtonScale);
    this->hoveredButton.setScale(hoveredButtonScale);
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

    this->mTextHovered.setFont(font);
    this->mTextHovered.setString(text);
    this->mTextHovered.setCharacterSize(boxSize.y*0.6);
    this->mTextHovered.setPosition(pos + sf::Vector2f((boxSize.x - mText.getLocalBounds().width)/2, boxSize.y*0.1));
    this->mTextHovered.setFillColor(textColorHoverred);

    this->mBoxHovered.setSize(boxSize);
    this->mBoxHovered.setPosition(pos);
    this->mBoxHovered.setFillColor(boxColorHoverred);
    this->mBoxHovered.setOutlineColor(boxOutlineColorHoverred);
    this->mBoxHovered.setOutlineThickness(outlineSize);  
}

void RectangleButton::setPosition(sf::Vector2f pos) {
    this->mBox.setPosition(pos);
    this->mBoxHovered.setPosition(pos);
    this->mText.setPosition(pos + sf::Vector2f((mBox.getSize().x - mText.getLocalBounds().width)/2, this->mBox.getSize().y*0.1));
    this->mTextHovered.setPosition(pos + sf::Vector2f((mBox.getSize().x - mText.getLocalBounds().width)/2, this->mBox.getSize().y*0.1));
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

void GraphicalNode::set(std::string string, sf::Font &font, double size , sf::Vector2f pos, sf::Color numColor, sf::Color boxColor, sf::Color boxOutlineColor) {
    number.setFont(font);
    number.setString(string);
    number.setCharacterSize(size);
    number.setPosition(pos);
    number.setFillColor(numColor);
    switch (string.size()) {
    case 1:
        number.setCharacterSize(size*0.8);
        number.setPosition(pos.x + size*0.4, pos.y + size*0.06);
        break;
    case 2:
        number.setCharacterSize(size*0.8);
        number.setPosition(pos.x + size*0.2, pos.y + size*0.06);
        break;
    case 3:
        number.setCharacterSize(size*0.7);
        number.setPosition(pos.x + size*0.08, pos.y + size*0.14);
        break;
    case 4:
        number.setCharacterSize(size*0.5);
        number.setPosition(pos.x + size*0.08, pos.y + size*0.26);
        break;
    case 5:
        number.setCharacterSize(size*0.4);
        number.setPosition(pos.x + size*0.08, pos.y + size*0.33);
        break;
    };
    this->box.setFillColor(boxColor);
    this->box.setSize(sf::Vector2f(size*1.2, size*1.2));
    this->box.setPosition(pos);
    this->box.setOutlineColor(boxOutlineColor);
    this->box.setOutlineThickness(0.1*size);
}

void GraphicalNode::setPos(sf::Vector2f pos) {
    std::string str = this->number.getString();
    switch (str.size()) {
    case 1:
        this->box.setPosition(pos);
        this->number.setPosition(pos.x + (box.getSize().x/1.2)*0.4, pos.y + (box.getSize().x/1.2)*0.06);
        break;
    case 2:
        this->box.setPosition(pos);
        this->number.setPosition(pos.x + (box.getSize().x/1.2)*0.2, pos.y + (box.getSize().x/1.2)*0.06);
        break;
    case 3:
        this->box.setPosition(pos);
        this->number.setPosition(pos.x + (box.getSize().x/1.2)*0.08, pos.y + (box.getSize().x/1.2)*0.14);
        break;
    case 4:
        this->box.setPosition(pos);
        this->number.setPosition(pos.x + (box.getSize().x/1.2)*0.08, pos.y + (box.getSize().x/1.2)*0.26);
        break;
    case 5:
        this->box.setPosition(pos);
        this->number.setPosition(pos.x + (box.getSize().x/1.2)*0.08, pos.y + (box.getSize().x/1.2)*0.33);
        break;
    };
}

void GraphicalNode::setColor(sf::Color textColor, sf::Color boxColor, sf::Color outlineColor) {
    this->number.setFillColor(textColor);
    this->box.setFillColor(boxColor);
    this->box.setOutlineColor(outlineColor);
}

void GraphicalNode::setSize(double size) {
    std::string string = this->number.getString();
    double oldSize = this->box.getSize().x/1.2;
    sf::Vector2f newPos = this->box.getPosition() + sf::Vector2f((oldSize - size)*1.2/2, (oldSize - size)*1.2/2);
    this->box.setSize(sf::Vector2f(size*1.2, size*1.2));
    this->box.setPosition(newPos);
    this->box.setOutlineThickness(size*0.1);
    double textSize;
    switch (string.size()) {
    case 1:
        textSize = size*0.8;
        newPos.x += size*0.4;
        newPos.y += size*0.06;  
        break;
    case 2:
        textSize = size*0.8;
        newPos.x += size*0.2;
        newPos.y += size*0.06;
        break;
    case 3:
        textSize = size*0.7;
        newPos.x += size*0.08;
        newPos.y += size*0.14;
        break;  
    case 4:
        textSize = size*0.5;
        newPos.x += size*0.08;
        newPos.y += size*0.26;
        break;
    case 5:
        textSize = size*0.4;
        newPos.x += size*0.08;
        newPos.y += size*0.33;
        break;
    };
    this->number.setPosition(newPos);
    this->number.setCharacterSize(textSize);
}

void GraphicalNode::setString(std::string string) {
    this->number.setString(string);
    setSize(this->box.getSize().x/1.2);
}
