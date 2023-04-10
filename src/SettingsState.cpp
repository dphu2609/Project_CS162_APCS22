#include <State/SettingsState.hpp>

SettingsState::SettingsState(sf::RenderWindow &window) : State(window) {
    loadTextures();
    loadFonts();
    buildScence();
    for (int i = 0; i < States::StatesCount; i++) {
        mStateActivated.push_back(0);
    }
    for (int i = 0; i < Action::ActionCount; i++) {
        mActionActivated.push_back(0);
    }
}

void SettingsState::loadTextures() {
    this->mTexturesHolder.load(Textures::playButton, "resources/img/playButton.png");
    this->mTexturesHolder.load(Textures::playButtonHoverred, "resources/img/playButtonHoverred.png");
    this->mTexturesHolder.load(Textures::pauseButton, "resources/img/pauseButton.png");
    this->mTexturesHolder.load(Textures::pauseButtonHoverred, "resources/img/pauseButtonHoverred.png");
    this->mTexturesHolder.load(Textures::replayButton, "resources/img/replayButton.png");
    this->mTexturesHolder.load(Textures::replayButtonHoverred, "resources/img/replayButtonHoverred.png");
    this->mTexturesHolder.load(Textures::nextButton, "resources/img/nextButton.png");
    this->mTexturesHolder.load(Textures::nextButtonHoverred, "resources/img/nextButtonHoverred.png");
    this->mTexturesHolder.load(Textures::prevButton, "resources/img/prevButton.png");
    this->mTexturesHolder.load(Textures::prevButtonHoverred, "resources/img/prevButtonHoverred.png");
    this->mTexturesHolder.load(Textures::speedButton, "resources/img/speedButton.png");
    this->mTexturesHolder.load(Textures::speedButtonHoverred, "resources/img/speedButtonHoverred.png");
    this->mTexturesHolder.load(Textures::speedCheckMark, "resources/img/speedCheckMark.png");
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
        mWindow, sf::Vector2f(500, sf::VideoMode::getDesktopMode().height - 170), 0,
        sf::Vector2f(20, 50), sf::Color(52, 53, 59, 255), sf::Color::Black
    );
    mSceneLayers[Containers]->attachChild(std::move(container));

    std::vector<std::string> dataTypeOptions = 
    {"Static Array", "Dynamic Array", "Singly Linked List",
    "Doubly Linked List", "Circular Linked List", "Stack", "Queue"}; 
    std::unique_ptr<DropBoxNode> newDataDropBox = std::make_unique<DropBoxNode>(
        mWindow, "SELECT DATA TYPE", dataTypeOptions, mFontsHolder[Fonts::RobotoRegular],
        sf::Vector2f(320, 50), 0, 0, sf::Vector2f(100, 100), 
        sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
        sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255),
        sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color::White,
        sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
    );
    mSceneLayers[DataDropBox]->attachChild(std::move(newDataDropBox));

    std::unique_ptr<ContainerNode> controlBoxContainer = std::make_unique<ContainerNode>(
        mWindow, sf::Vector2f(700, 13resources/0), 0,
        sf::Vector2f((sf::VideoMode::getDesktopMode().width - 700)/2, sf::VideoMode::getDesktopMode().height - 270 + 300), sf::Color(52, 53, 59, 255), sf::Color::Black
    );
    mSceneLayers[ControlBoxContainer]->attachChild(std::move(controlBoxContainer));

    std::unique_ptr<ImageButtonNode> pauseButton = std::make_unique<ImageButtonNode>(
        mWindow, this->mTexturesHolder[Textures::pauseButton], this->mTexturesHolder[Textures::pauseButtonHoverred],
        sf::Vector2f(30, 30), sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30)/2 - 100, sf::VideoMode::getDesktopMode().height - 220 + 300)
    );
    mSceneLayers[ControlBoxButtons]->attachChild(std::move(pauseButton));

    std::unique_ptr<ImageButtonNode> nextButton = std::make_unique<ImageButtonNode>(
        mWindow, this->mTexturesHolder[Textures::nextButton], this->mTexturesHolder[Textures::nextButtonHoverred],
        sf::Vector2f(30, 30), sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30)/2 + 70 - 100, sf::VideoMode::getDesktopMode().height - 220 + 300)
    );
    mSceneLayers[ControlBoxButtons]->attachChild(std::move(nextButton));

    std::unique_ptr<ImageButtonNode> prevButton = std::make_unique<ImageButtonNode>(
        mWindow, this->mTexturesHolder[Textures::prevButton], this->mTexturesHolder[Textures::prevButtonHoverred],
        sf::Vector2f(30, 30), sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30)/2 - 70 - 100, sf::VideoMode::getDesktopMode().height - 220 + 300)
    );
    mSceneLayers[ControlBoxButtons]->attachChild(std::move(prevButton));

    std::unique_ptr<ImageButtonNode> speedButton = std::make_unique<ImageButtonNode>(
        mWindow, this->mTexturesHolder[Textures::speedButton], this->mTexturesHolder[Textures::speedButtonHoverred],
        sf::Vector2f(30, 30), sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30)/2 + 100, sf::VideoMode::getDesktopMode().height - 220 + 300)
    );
    mSceneLayers[ControlBoxSpeedButton]->attachChild(std::move(speedButton));
}

void SettingsState::activeSettings(sf::Time dt) {
    sf::Vector2i localPosition(sf::Mouse::getPosition(this->mWindow));
    sf::Vector2f localPositionF(static_cast<double>(localPosition.x), static_cast<double>(localPosition.y));
    localPositionF = mWindow.mapPixelToCoords(localPosition);
    bool isInputBoxActivated = 0;
    for (auto &child : mSceneLayers[InputBox]->getChildren()) {
        isInputBoxActivated |= child->isActivated();
    }
    if (localPositionF.x <= 40 && !this->mIsEmerged) {
        this->elapsedTime = 0.f;
        settingsIn(dt);
    }
    else if (mActionActivated[Action::Play] && this->mIsEmerged && !mActionActivated[Action::Create]) {
        settingsOut(dt);
        if (!this->mIsControlBoxEmerged) {
            controlBoxIn(dt);
        }
    }
    else if (localPositionF.x >= 520 && this->mIsEmerged && !isInputBoxActivated && !mFirstTimeVisited) {
        this->elapsedTime += clock.restart().asSeconds(); 
        if (elapsedTime >= 3.f)
            settingsOut(dt);
    }
    else {
        this->elapsedTime = 0.f;
        clock.restart();
    }
    if (mActionActivated[Action::ResetAction]) {
        if (this->mIsControlBoxEmerged) {
            controlBoxOut(dt);
        }
    }
}

void SettingsState::controlBoxIn(sf::Time dt) {
    for (int i = Error + 1; i < LayerCount; i++) {
        for (auto &child : this->mSceneLayers[i]->getChildren()) {
            if (!child->mIsMoving) {
                child->triggerMoveAnimation(dt, 3, 300, -90);
                this->mIsControlBoxEmerged = 1;
            }
        }
    }
}

void SettingsState::controlBoxOut(sf::Time dt) {
    for (int i = Error + 1; i < LayerCount; i++) {
        for (auto &child : this->mSceneLayers[i]->getChildren()) {
            if (!child->mIsMoving) {
                child->triggerMoveAnimation(dt, 1.6, 300, 90);
                this->mIsControlBoxEmerged = 0;
            }
        }
    }
}

void SettingsState::settingsIn(sf::Time dt) {
    for (int i = 0; i < Error; i++) {
        for (auto &child : this->mSceneLayers[i]->getChildren()) {
            if (!child->mIsMoving) {
                child->triggerMoveAnimation(dt, 1, 600, 0);
                this->mIsEmerged = 1;
            }
        }
    }
}

void SettingsState::settingsOut(sf::Time dt) {
    for (int i = 0; i < Error; i++) {
        for (auto &child : this->mSceneLayers[i]->getChildren()) {
            if (!child->mIsMoving) {
                child->triggerMoveAnimation(dt, 1.6, 600, 180);
                this->mIsEmerged = 0;
            }
        }
    }
    this->mSceneLayers[Error]->getChildren().clear();
}

void SettingsState::controlEvent(sf::Event &event) {
    handleDataDropBoxEvent(event);
    handleActionDropBoxEvent(event);
    handleAction(event);
    handleControlBoxEvent(event);
}