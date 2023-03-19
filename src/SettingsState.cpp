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
    std::unique_ptr newContainer = std::make_unique<ContainerNode>(
        mWindow, sf::Vector2f(500, sf::VideoMode::getDesktopMode().height - 100), 0,
        sf::Vector2f(20 - 600, 50), sf::Color(52, 53, 59, 255), sf::Color::Black
    );
    mSceneLayers[Containers]->attachChild(std::move(newContainer));
}

void SettingsState::handleEvent() {
}

void SettingsState::activeSettings(sf::Time dt) {
    sf::Vector2i localPosition(sf::Mouse::getPosition(this->mWindow));
    if (localPosition.x <= 20 && !this->mIsEmerged) {
        this->mIsEmerged = 1;
        this->elapsedTime = 0.f;
        for (auto &child : this->mSceneLayers[Containers]->getChildren()) {
            child->triggerMoveAnimation(dt, 1, 600, 0);
        }
    }
    else if (localPosition.x >= 520 && this->mIsEmerged) {
        this->elapsedTime += clock.restart().asSeconds();
        if (elapsedTime >= 2.f) {
            this->mIsEmerged = 0;
            for (auto &child : this->mSceneLayers[Containers]->getChildren()) {
                child->triggerMoveAnimation(dt, 1, 600, 180);
            }
        }
    }
    else clock.restart();
}