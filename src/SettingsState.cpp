#include <State/SettingsState.hpp>

SettingsState::SettingsState(sf::RenderWindow &window) : State(window) {
    loadTextures();
    loadFonts();
    buildScence();
    this->mIsEmerged = 0;
    for (int i = 0; i < States::StatesCount; i++) {
        mIsStateActivated.push_back(0);
    }
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

    std::vector<std::string> dataTypeOptions = {"Array", "Linked List"};
    std::unique_ptr<DropBoxNode> newDataDropBox = std::make_unique<DropBoxNode>(
        mWindow, "SELECT DATA TYPE", dataTypeOptions, mFontsHolder[Fonts::RobotoRegular],
        sf::Vector2f(320, 50), 0, 0, sf::Vector2f(100 - 600, 100), 
        sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
        sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255),
        sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color::White,
        sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
    );
    mSceneLayers[DropBox]->attachChild(std::move(newDataDropBox));

    std::vector<std::string> actionOptions = {"Create", "Insert", "Delete", "Search"};
    std::unique_ptr<DropBoxNode> newActionDropBox = std::make_unique<DropBoxNode>(
        mWindow, "ACTION", actionOptions, mFontsHolder[Fonts::RobotoRegular],
        sf::Vector2f(180, 50), 0, 0, sf::Vector2f(160 - 600, sf::VideoMode::getDesktopMode().height - 500), 
        sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
        sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255),
        sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color::White,
        sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
    );
    mSceneLayers[DropBox]->attachChild(std::move(newActionDropBox));

    std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
        mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(400, 50), 2, 
        sf::Vector2f(100 - 600, 800), sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
    );
    mSceneLayers[InputBox]->attachChild(std::move(newInputBox));
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
        for (auto &child : this->mSceneLayers[DropBox]->getChildren()) {
            if (!child->mIsMoving) {
                child->triggerMoveAnimation(dt, 1, 600, 0);
            }
        }
        for (auto &child : this->mSceneLayers[InputBox]->getChildren()) {
            if (!child->mIsMoving) {
                child->triggerMoveAnimation(dt, 1, 600, 0);
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
            for (auto &child : this->mSceneLayers[DropBox]->getChildren()) {
                if (!child->mIsMoving) {
                    child->triggerMoveAnimation(dt, 1.25, 600, 180);
                }
            }
            for (auto &child : this->mSceneLayers[InputBox]->getChildren()) {
                if (!child->mIsMoving) {
                    child->triggerMoveAnimation(dt, 1.25, 600, 180);
                }
            }
        }
    }
    else {
        elapsedTime = 0.f;
        clock.restart();
    }
}

void SettingsState::handleClick(sf::Event &event) {
    int index = 0;
    for (auto &child : this->mSceneLayers[DropBox]->getChildren()) {
        switch (index) {
            case 0: {
                if (child->getClickedIndex(event) == 2) mIsStateActivated[States::SinglyLinkedList] = 1;
                break;
            }
            case 1: {
                // if (child->getClickedIndex(event) == 2)
            }
        }
        index++;
    }
}