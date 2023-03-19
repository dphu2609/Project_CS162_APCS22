#include <State/SettingsState.hpp>

SettingsState::SettingsState(sf::RenderWindow &window) : State(window) {
    loadTextures();
    loadFonts();
    buildScence();
    this->mIsEmerged = 0;
}

void SettingsState::loadTextures() {
}

void SettingsState::loadFonts() {
    this->mFontsHolder.load(Fonts::RobotoRegular, "fonts/Roboto/Roboto-Regular.ttf");
}

void SettingsState::buildScence() {
    for (int i = 0; i < LayerCount; i++) {
        std::unique_ptr<SceneNode> layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }
    std::unique_ptr<ContainerNode> container = std::make_unique<ContainerNode>(
        mWindow, sf::Vector2f(500, sf::VideoMode::getDesktopMode().height - 100), 0,
        sf::Vector2f(20 - 600, 50), sf::Color(52, 53, 59, 255), sf::Color::Black
    );
    mSceneLayers[Containers]->attachChild(std::move(container));
    std::vector<std::string> options = {"SINGLY", "DOUBLY", "ORDERRED", "CIRCULAR"};
    std::unique_ptr<DropBoxNode> newDropBox = std::make_unique<DropBoxNode>(
        mWindow, "LINKED LIST", options, mFontsHolder[Fonts::RobotoRegular],
        sf::Vector2f(300, 80), 10, 5, sf::Vector2f(120, 400), 
        sf::Color::White, sf::Color(120, 140, 98, 255), sf::Color(51, 59, 42, 255),
        sf::Color::White, sf::Color(81, 68, 105, 255), sf::Color(46, 38, 61, 255),
        sf::Color::White, sf::Color(89, 113, 158, 255), sf::Color::White,
        sf::Color::White, sf::Color(49, 58, 74, 255), sf::Color::White
    );
    mSceneLayers[DropBox]->attachChild(std::move(newDropBox));
}

void SettingsState::activeSettings(sf::Time dt) {
    sf::Vector2i localPosition(sf::Mouse::getPosition(this->mWindow));
    if (localPosition.x <= 20 && !this->mIsEmerged) {
        this->elapsedTime = 0.f;
        for (auto &child : this->mSceneLayers[Containers]->getChildren()) {
            if (!child->mIsMoving) {
                child->triggerMoveAnimation(dt, 1, 600, 0);
                this->mIsEmerged = 1;
            }
        }
    }
    else if (localPosition.x >= 520 && this->mIsEmerged) {
        this->elapsedTime += clock.restart().asSeconds();
        if (elapsedTime >= 2.5) {
            for (auto &child : this->mSceneLayers[Containers]->getChildren()) {
                if (!child->mIsMoving) {
                    child->triggerMoveAnimation(dt, 1.25, 600, 180);
                    this->mIsEmerged = 0;
                }
            }
        }
    }
    else {
        elapsedTime = 0.f;
        clock.restart();
    }
}