#include <SceneGraph/ImageButtonNode.hpp>

ImageButtonNode::ImageButtonNode(sf::RenderWindow &window, sf::Texture &originalButtonTexture, sf::Texture &hoverredButtonTexture, sf::Vector2f size, sf::Vector2f pos) : mWindow(window) {
    this->mButton.set(originalButtonTexture, hoverredButtonTexture, size.x, size.y, pos);
}

void ImageButtonNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    if (evn::isHoverred(this->mWindow, this->mButton.originalButton)) {
        target.draw(this->mButton.hoverredButton);
    }
    else target.draw(this->mButton.originalButton);
}

int ImageButtonNode::getClickedIndex(sf::Event &event) {
    if (evn::isLeftClicked(mWindow, event, this->mButton.originalButton)) {
        return 0;
    }
    return -1;
}
