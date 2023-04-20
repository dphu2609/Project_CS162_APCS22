#include <State/MenuState.hpp>

MenuState::MenuState(sf::RenderWindow &window) : State(window) {
    loadTextures();
    loadFonts();
    buildScence();
}

void MenuState::loadTextures() {
    this->mTexturesHolder.load(Textures::menuBackGround, "resources/img/menu_background2.jpg");
}

void MenuState::loadFonts() {
    this->mFontsHolder.load(Fonts::GreatVibesRegular, "resources/fonts/GreatVibes-Regular.ttf");
}

void MenuState::buildScence() {
    for (int i = 0; i < LayerCount; i++) {
        std::unique_ptr<SceneNode> layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    std::unique_ptr<SpriteNode> menuBackGround = std::make_unique<SpriteNode>(
        mTexturesHolder[Textures::menuBackGround], 
        sf::Vector2f(sf::VideoMode::getDesktopMode().width - 35, sf::VideoMode::getDesktopMode().height - 70),
        sf::Vector2f(0, 0), 0
    );
    mSceneLayers[Background]->attachChild(std::move(menuBackGround));

    std::unique_ptr<RectangleButtonNode> label = std::make_unique<RectangleButtonNode>(
        mWindow, "Data Visual", mFontsHolder[Fonts::GreatVibesRegular],
        sf::Vector2f(1000*Constant::scaleX, 500*Constant::scaleY), 0,
        sf::Vector2f((sf::VideoMode::getDesktopMode().width - 35)/2 - 500*Constant::scaleX, 200*Constant::scaleY),
        sf::Color(179, 201, 230, 255), sf::Color::Transparent, sf::Color::Transparent,
        sf::Color(179, 201, 230, 255), sf::Color::Transparent, sf::Color::Transparent   
    );
    mSceneLayers[Label]->attachChild(std::move(label));
    
    std::unique_ptr<RectangleButtonNode> button1 = std::make_unique<RectangleButtonNode>(
        mWindow, "start", mFontsHolder[Fonts::GreatVibesRegular],
        sf::Vector2f(1000*Constant::scaleX, 300*Constant::scaleY), 0,
        sf::Vector2f((sf::VideoMode::getDesktopMode().width - 35)/2 - 500*Constant::scaleX, 800*Constant::scaleY),
        sf::Color(179, 201, 230, 255), sf::Color::Transparent, sf::Color::Transparent,
        sf::Color(230, 179, 190, 255), sf::Color::Transparent, sf::Color::Transparent   
    );
    mSceneLayers[Buttons]->attachChild(std::move(button1));

    std::unique_ptr<RectangleButtonNode> button2 = std::make_unique<RectangleButtonNode>(
        mWindow, "exit", mFontsHolder[Fonts::GreatVibesRegular],
        sf::Vector2f(1000*Constant::scaleX, 300*Constant::scaleY), 0,
        sf::Vector2f((sf::VideoMode::getDesktopMode().width - 35)/2 - 500*Constant::scaleX, 1100*Constant::scaleY),
        sf::Color(179, 201, 230, 255), sf::Color::Transparent, sf::Color::Transparent,
        sf::Color(230, 179, 190, 255), sf::Color::Transparent, sf::Color::Transparent   
    );
    mSceneLayers[Buttons]->attachChild(std::move(button2));
}

void MenuState::handleMenuEvent(sf::Event &event) {
    int index = 0;
    for (auto &child : mSceneLayers[Buttons]->getChildren()) {
        if (child->getClickedIndex(event) == 0) {
            if (index == 0) {
                mIsProgramStarted = 1;
            } else if (index == 1) {
                mWindow.close();
            }
        }
        index++;
    }
}