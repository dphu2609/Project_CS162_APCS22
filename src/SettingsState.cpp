#include <State/SettingsState.hpp>

SettingsState::SettingsState(sf::RenderWindow &window) : State(window) {
    loadTextures();
    loadFonts();
    buildScence();
    this->mIsEmerged = 0;
    for (int i = 0; i < States::StatesCount; i++) {
        mIsStateActivated.push_back(0);
    }
    for (int i = 0; i < Action::ActionCount; i++) {
        mActionActivated.push_back(0);
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

    std::vector<std::string> dataTypeOptions = {"Array", "Linked List"}; //data drop box
    std::unique_ptr<DropBoxNode> newDataDropBox = std::make_unique<DropBoxNode>(
        mWindow, "SELECT DATA TYPE", dataTypeOptions, mFontsHolder[Fonts::RobotoRegular],
        sf::Vector2f(320, 50), 0, 0, sf::Vector2f(100 - 600, 100), 
        sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
        sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255),
        sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color::White,
        sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
    );
    mSceneLayers[DropBox]->attachChild(std::move(newDataDropBox));

    std::vector<std::string> actionOptions = {"Create", "Insert", "Delete", "Update", "Search"}; //action drop box
    std::unique_ptr<DropBoxNode> newActionDropBox = std::make_unique<DropBoxNode>(
        mWindow, "ACTION", actionOptions, mFontsHolder[Fonts::RobotoRegular],
        sf::Vector2f(180, 50), 0, 0, sf::Vector2f(160 - 600, sf::VideoMode::getDesktopMode().height - 500), 
        sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
        sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255),
        sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color::White,
        sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
    );
    mSceneLayers[DropBox]->attachChild(std::move(newActionDropBox));
}

void SettingsState::activeSettings(sf::Time dt) {
    sf::Vector2i localPosition(sf::Mouse::getPosition(this->mWindow));
    sf::Vector2f localPositionF(static_cast<float>(localPosition.x), static_cast<float>(localPosition.y));
    localPositionF = mWindow.mapPixelToCoords(localPosition);
    if (localPositionF.x <= 20 && !this->mIsEmerged) {
        this->elapsedTime = 0.f;
        for (int i = 0; i < LayerCount; i++) {
            for (auto &child : this->mSceneLayers[i]->getChildren()) {
                if (!child->mIsMoving) {
                    child->triggerMoveAnimation(dt, 1, 600, 0);
                }
            }
        }
        this->mIsEmerged = 1;
    }
    else if (localPositionF.x >= 520 && this->mIsEmerged) {
        this->elapsedTime += clock.restart().asSeconds();
        if (elapsedTime >= 3.f) {
            for (int i = 0; i < LayerCount; i++) {
                for (auto &child : this->mSceneLayers[i]->getChildren()) {
                    if (!child->mIsMoving) {
                        child->triggerMoveAnimation(dt, 1.25, 600, 180);
                    }
                }
            }
            this->mIsEmerged = 0;
        }
    }
    else {
        elapsedTime = 0.f;
        clock.restart();
    }
}

void SettingsState::handleInput(sf::Event &event) {
    int index = 0;
    for (auto &child : this->mSceneLayers[DropBox]->getChildren()) {
        switch (index) {
            case 0: {
                if (child->getClickedIndex(event) == 2) mIsStateActivated[States::SinglyLinkedList] = 1;
                break;
            }
            case 1: {
                switch(child->getClickedIndex(event)) {
                    case Action::Create : {
                        if (this->mSceneLayers[InputBox]->getChildren().size() == 0) {
                            std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
                                mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(250, 40), 2, 
                                sf::Vector2f(125, sf::VideoMode::getDesktopMode().height - 280), 
                                sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                            );
                            this->mSceneLayers[InputBox]->attachChild(std::move(newInputBox));

                            std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Random", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 400),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                            std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Custom", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 340),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));
                            this->mActionActivated[Action::Create] = 1;
                        }
                        break;
                    }
                    case Action::Insert : {
                        if (this->mSceneLayers[InputBox]->getChildren().size() == 0) {
                            std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
                                mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(250, 40), 2, 
                                sf::Vector2f(125, sf::VideoMode::getDesktopMode().height - 230), 
                                sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                            );
                            this->mSceneLayers[InputBox]->attachChild(std::move(newInputBox));

                            std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Insert Head", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 420),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                            std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Insert Tail", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 360),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                            std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Custom Index", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 300),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton3));
                            this->mActionActivated[Action::Insert] = 1;
                        }
                        break;
                    }
                    case Action::Delete : {
                        if (this->mSceneLayers[InputBox]->getChildren().size() == 0) {
                            std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
                                mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(250, 40), 2, 
                                sf::Vector2f(125, sf::VideoMode::getDesktopMode().height - 230), 
                                sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                            );
                            this->mSceneLayers[InputBox]->attachChild(std::move(newInputBox));

                            std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Delete Head", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 420),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                            std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Delete Tail", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 360),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                            std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Custom Index", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 300),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton3));
                            this->mActionActivated[Action::Delete] = 1;
                        }
                        break;
                    }
                    case Action::Update : {
                        if (this->mSceneLayers[InputBox]->getChildren().size() == 0) {
                            std::unique_ptr<InputBoxNode> newInputBox1 = std::make_unique<InputBoxNode>(
                                mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(120, 40), 2, 
                                sf::Vector2f(120, sf::VideoMode::getDesktopMode().height - 350), 
                                sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                            );
                            this->mSceneLayers[InputBox]->attachChild(std::move(newInputBox1));

                            std::unique_ptr<InputBoxNode> newInputBox2 = std::make_unique<InputBoxNode>(
                                mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(120, 40), 2, 
                                sf::Vector2f(260, sf::VideoMode::getDesktopMode().height - 350), 
                                sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                            );
                            this->mSceneLayers[InputBox]->attachChild(std::move(newInputBox2));

                            std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Index", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(130, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 420),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                            std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(130, 50), 0,
                                sf::Vector2f(250, sf::VideoMode::getDesktopMode().height - 420),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));
                            this->mActionActivated[Action::Update] = 1;
                        }
                        break;
                    }
                    case Action::Search : {
                        if (this->mSceneLayers[InputBox]->getChildren().size() == 0) {
                            std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
                                mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(250, 40), 2, 
                                sf::Vector2f(125, sf::VideoMode::getDesktopMode().height - 280), 
                                sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                            );
                            this->mSceneLayers[InputBox]->attachChild(std::move(newInputBox));

                            std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Random Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 400),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                            std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Custom Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 340),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));
                            this->mActionActivated[Action::Search] = 1;
                        }
                        break;
                    }
                    case Action::ResetAction : {
                        if (this->mSceneLayers[InputBox]->getChildren().size() > 0) {
                            this->mSceneLayers[InputBox]->getChildren().clear();
                            this->mSceneLayers[ActionButtons]->getChildren().clear();
                            for (auto &action : mActionActivated) {
                                action = 0;
                            }
                        }
                        break;
                    }
                }
                break;
            }
        }
        index++;
    }
}

void SettingsState::createRandomList() {
    srand((unsigned int)time(NULL));
    int size = rand() % 4 + 3;
    mInputArr.resize(size);
    for (int i = 0; i < size; i++) {
        mInputArr[i] = rand()% 100;
    }
}

void SettingsState::handleAction(sf::Event &event) {
    int index = 0;
    for (int i = 0; i < Action::ActionCount; i++) {
        if (mActionActivated[i]) {
            index = i;
            break;
        }
    }
    switch(index) {
        case Action::Create : {
            int btnIndex = 0;
            for (auto &child : mSceneLayers[ActionButtons]->getChildren()) {
                switch (btnIndex) {
                    case 0 : {
                        if (child->getClickedIndex(event) == 0) {
                            createRandomList();
                            for (auto &child : mSceneLayers[InputBox]->getChildren()) {

                            }
                        }
                    }
                }
                btnIndex++;
            }
        }
    }
}