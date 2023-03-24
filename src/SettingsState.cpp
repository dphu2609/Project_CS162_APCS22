#include <State/SettingsState.hpp>

SettingsState::SettingsState(sf::RenderWindow &window) : State(window) {
    loadTextures();
    loadFonts();
    buildScence();
    this->mIsEmerged = 0;
    for (int i = 0; i < States::StatesCount; i++) {
        mStateActivated.push_back(0);
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
    bool isInputBoxActivated = 0;
    for (auto &child : mSceneLayers[InputBox]->getChildren()) {
        isInputBoxActivated |= child->isActivated();
    }
    if (localPositionF.x <= 40 && !this->mIsEmerged) {
        this->elapsedTime = 0.f;
        settingsIn(dt);
    }
    else if (mActionActivated[Action::Insert] && mActionActivated[Action::Play]) {
        settingsOut(dt);
    }
    else if (localPositionF.x >= 520 && this->mIsEmerged && !isInputBoxActivated) {
        this->elapsedTime += clock.restart().asSeconds();
        if (elapsedTime >= 3.f)
            settingsOut(dt);
    }
    else {
        this->elapsedTime = 0.f;
        clock.restart();
    }
}

void SettingsState::settingsIn(sf::Time dt) {
    for (int i = 0; i < LayerCount - 1; i++) {
        for (auto &child : this->mSceneLayers[i]->getChildren()) {
            if (!child->mIsMoving) {
                child->triggerMoveAnimation(dt, 1, 600, 0);
                this->mIsEmerged = 1;
            }
        }
    }
}

void SettingsState::settingsOut(sf::Time dt) {
    for (int i = 0; i < LayerCount - 1; i++) {
        for (auto &child : this->mSceneLayers[i]->getChildren()) {
            if (!child->mIsMoving) {
                child->triggerMoveAnimation(dt, 1.6, 600, 180);
                this->mIsEmerged = 0;
            }
        }
    }
    for (auto &child : this->mSceneLayers[Error]->getChildren()) {
        if (!child->mIsMoving) {
            child->triggerMoveAnimation(dt, 1.6, 200, 90);
        }
    }
}

void SettingsState::handleActionDropBoxEvent(sf::Event &event) {
    int index = 0;
    for (auto &child : this->mSceneLayers[DropBox]->getChildren()) {
        switch (index) {
            case 0: {
                if (child->getClickedIndex(event) == 2) mStateActivated[States::SinglyLinkedList] = 1;
                break;
            }
            case 1: {
                switch(child->getClickedIndex(event)) {
                    case Action::Create : {
                        if (this->mSceneLayers[InputBox]->getChildren().size() == 0) {
                            std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
                                mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(300, 40), 2, 
                                sf::Vector2f(100, sf::VideoMode::getDesktopMode().height - 280), 
                                sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                            );
                            this->mSceneLayers[InputBox]->attachChild(std::move(newInputBox));

                            std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Random", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 400),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                            std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Custom input: ", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(180, 45), 0,
                                sf::Vector2f(100, sf::VideoMode::getDesktopMode().height - 330),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                            std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Go", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80, 40), 0,
                                sf::Vector2f(420, sf::VideoMode::getDesktopMode().height - 280),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton3));
                            this->mActionActivated[Action::Create] = 1;
                        }
                        break;
                    }
                    case Action::Insert : {
                        if (this->mSceneLayers[InputBox]->getChildren().size() == 0) {
                            std::unique_ptr<InputBoxNode> newInputBox1 = std::make_unique<InputBoxNode>(
                                mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(120, 40), 2, 
                                sf::Vector2f(120, sf::VideoMode::getDesktopMode().height - 230), 
                                sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                            );
                            this->mSceneLayers[InputBox]->attachChild(std::move(newInputBox1));

                            std::unique_ptr<InputBoxNode> newInputBox2 = std::make_unique<InputBoxNode>(
                                mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(120, 40), 2, 
                                sf::Vector2f(260, sf::VideoMode::getDesktopMode().height - 230), 
                                sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                            );
                            this->mSceneLayers[InputBox]->attachChild(std::move(newInputBox2));

                            std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Insert Head", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 420),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                            std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Insert Tail", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 360),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                            std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Index", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(130, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 300),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton3));

                            std::unique_ptr<RectangleButtonNode> newButton4 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(130, 50), 0,
                                sf::Vector2f(250, sf::VideoMode::getDesktopMode().height - 300),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton4));

                            std::unique_ptr<RectangleButtonNode> newButton5 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Go", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80, 40), 0,
                                sf::Vector2f(420, sf::VideoMode::getDesktopMode().height - 230),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton5));
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
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                            std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Delete Tail", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 360),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                            std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Custom Index", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 300),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
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
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                            std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(130, 50), 0,
                                sf::Vector2f(250, sf::VideoMode::getDesktopMode().height - 420),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
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
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                            std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Custom Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280, 50), 0,
                                sf::Vector2f(110, sf::VideoMode::getDesktopMode().height - 340),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
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
                            for (int i = 0; i < mActionActivated.size(); i++) {
                                mActionActivated[i] = 0;
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

void SettingsState::throwError(const std::string &errorMessage) {
    mSceneLayers[Error]->getChildren().clear();
    std::unique_ptr<RectangleButtonNode> newError = std::make_unique<RectangleButtonNode>(
        mWindow, errorMessage, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(errorMessage.size()*20, 40), 0,
        sf::Vector2f((sf::VideoMode::getDesktopMode().width - errorMessage.size()*20)/2, sf::VideoMode::getDesktopMode().height - 100),
        sf::Color(201, 52, 112, 255), sf::Color(52, 53, 59, 255), sf::Color::White,
        sf::Color(201, 52, 112, 255), sf::Color(41, 58, 117, 255), sf::Color::White
    );
    this->mSceneLayers[Error]->attachChild(std::move(newError));
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
                                std::string str = "";
                                for (int i = 0; i < mInputArr.size() - 1; i++) {
                                    str += std::to_string(mInputArr[i]) + ", ";
                                }
                                str += std::to_string(mInputArr.back());
                                child->resetContent(str);
                                break;
                            }
                        }
                        break;
                    }
                    case 2 : {
                        if (child->getClickedIndex(event) == 0 && mInputArr.size() > 0) {
                            for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                this->mInputArr = child->getIntArrayData();
                            }
                            if (mInputArr.size() <= 10) {
                                mActionActivated[Action::Play] = 1;
                            }
                        }
                        break;
                    }
                }
                btnIndex++;
            }
            break;
        }

        case Action::Insert : {
            int btnIndex = 0;
            for (auto &child : mSceneLayers[ActionButtons]->getChildren()) {
                switch (btnIndex) {
                    case 0: {
                        if (child->getClickedIndex(event) == 0) {
                            mActionIndex = 0;
                            for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                child->resetContent("0");
                                break;
                            }
                        }
                        break;
                    }
                    case 1: {
                        if (child->getClickedIndex(event) == 0) {
                            mActionIndex = mInputArr.size();
                            for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                child->resetContent(std::to_string(mActionIndex));
                                break;
                            }
                        }
                        break;
                    }
                    case 4: {
                        if (child->getClickedIndex(event) == 0) {
                            std::vector<int> indexInput;
                            std::vector<int> dataInput;
                            int inputBoxIndex = 0;
                            for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                if (inputBoxIndex == 0) {
                                    indexInput = child->getIntArrayData();
                                } else if (inputBoxIndex == 1) {
                                    dataInput = child->getIntArrayData();
                                }
                                inputBoxIndex++;
                            } 
                            if (indexInput.size() != 1) {
                                throwError("Error: Invalid index!");
                            } else if (indexInput[0] > mInputArr.size() || indexInput[0] < 0) {
                                std::string message = "";
                                if (mInputArr.size() == 0) message = "Error: List is empty! Index must be 0!";
                                else message = "Error: Index must be in range from 0 to " + std::to_string(mInputArr.size()) + "!";
                                throwError(message);
                            } else if (dataInput.size() != 1) {
                                throwError("Error: Invalid value!");
                            } else if (mInputArr.size() >= 10) {
                                throwError("Sorry, the maximum size is 10.");
                            } 
                            else if (!mIsActionActivating) {
                                mActionActivated[Action::Play] = 1;
                                mActionIndex = indexInput[0];
                                mInsertValue = dataInput[0];
                                mSceneLayers[Error]->getChildren().clear();
                                mInputArr.insert(mInputArr.begin() + mActionIndex, mInsertValue);
                                mIsEmerged = 0;
                                std::cout << mInputArr.size() << ' ';
                            }
                        }
                        break;
                    }
                }
                btnIndex++;
            }
            break;
        }
    }
}