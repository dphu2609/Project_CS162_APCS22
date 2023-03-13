#include <SceneGraph/ButtonNode.hpp>

ButtonNode::ButtonNode(sf::RenderWindow &window, sf::Texture &originalButtonTexture, sf::Texture &hoverredButtonTexture, sf::Vector2f size, sf::Vector2f pos) : mWindow(window) {
    this->mButton.set(originalButtonTexture, hoverredButtonTexture, size.x, size.y, pos);
}

void ButtonNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    if (evn::isHoverred(this->mWindow, this->mButton.originalButton)) {
        target.draw(this->mButton.hoverredButton);
    }
    else target.draw(this->mButton.originalButton);
}

bool ButtonNode::isLeftClicked() {
    return evn::isLeftClicked(this->mWindow, this->mButton.originalButton);
}
