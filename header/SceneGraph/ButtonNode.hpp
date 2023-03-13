#pragma once
#include <SceneGraph/SceneNode.hpp>

namespace ButtonType {
    enum ID {
        Create,
        Insert,
        Search,
        Delete,
        Return,
        TypeCount
    };
};

class ButtonNode : public SceneNode {
public:
    ButtonNode(sf::RenderWindow &window, sf::Texture &originalButtonTexture, sf::Texture &hoverredButtonTexture, sf::Vector2f size, sf::Vector2f pos);
    virtual bool isLeftClicked();
private:
    ImageButton mButton;
    sf::RenderWindow &mWindow;
private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
};
