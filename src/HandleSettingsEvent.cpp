#include <State/SettingsState.hpp>

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

                            std::unique_ptr<RectangleButtonNode> newButton4 = std::make_unique<RectangleButtonNode>(
                                mWindow, "Go", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80, 40), 0,
                                sf::Vector2f(420, sf::VideoMode::getDesktopMode().height - 230),
                                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                            );
                            this->mSceneLayers[ActionButtons]->attachChild(std::move(newButton4));
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
    std::cout << 1;
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
                        if (child->getClickedIndex(event) == 0) {
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
                                mTypeOfAction = Action::Insert;
                            }
                        }
                        break;
                    }
                }
                btnIndex++;
            }
            break;
        }

        case Action::Delete: {
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
                            mActionIndex = mInputArr.size() - 1;
                            for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                child->resetContent(std::to_string(mActionIndex));
                                break;
                            }
                        }
                        break;
                    }
                    case 3: {
                        if (child->getClickedIndex(event) == 0) {
                            std::vector<int> indexInput;
                            for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                indexInput = child->getIntArrayData();
                            } 
                            if (indexInput.size() != 1) {
                                throwError("Error: Invalid index!");
                            } else if (indexInput[0] > mInputArr.size() - 1 || indexInput[0] < 0) {
                                std::string message = "";
                                if (mInputArr.size() == 0) message = "Error: List is empty! Can not perform this action.";
                                else message = "Error: Index must be in range from 0 to " + std::to_string(mInputArr.size() - 1) + "!";
                                throwError(message);
                            } else if (mInputArr.size() == 0) {
                                throwError("Error: List is empty! Can not perform this action.");
                            }
                            else if (!mIsActionActivating) {
                                mActionActivated[Action::Play] = 1;
                                mActionIndex = indexInput[0];
                                mDeleteValue = mInputArr[mActionIndex];
                                mSceneLayers[Error]->getChildren().clear();
                                mTypeOfAction = Action::Delete;
                            }
                        }
                        break;
                    }
                }
                btnIndex++;
            }
        }
    }
}

void SettingsState::handleControlBoxEvent(sf::Event &event) {
    int index = 0;
    for (auto &child : mSceneLayers[ControlBoxButtons]->getChildren()) {
        switch (index) {
            case 0: {
                if (child->getClickedIndex(event) == 0) {
                    if (mIsEndAnimation.first && mIsEndAnimation.second) {
                        switch (mTypeOfAction) {
                            case Action::Insert: {
                                mInputArr.erase(mInputArr.begin() + mActionIndex);
                                break;
                            }
                            case Action::Delete: {
                                mInputArr.insert(mInputArr.begin() + mActionIndex, mDeleteValue);
                                break;
                            }
                        }
                        mActionActivated[Action::Play] = 1;
                        mIsReplayAction = 1;
                        mIsActionPaused = 1;
                        mIsEndAnimation.second = 0;
                        mIsEndAnimation.first = 0;
                    }
                    if (!mIsActionPaused) mIsActionPaused = 1;
                    else mIsActionPaused = 0;
                    if (mIsActionPaused) {
                        std::unique_ptr<ImageButtonNode> playButton = std::make_unique<ImageButtonNode>(
                            mWindow, this->mTexturesHolder[Textures::playButton], this->mTexturesHolder[Textures::playButtonHoverred],
                            sf::Vector2f(30, 30), sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30)/2, sf::VideoMode::getDesktopMode().height - 150)
                        );
                        mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(playButton);
                    } else {
                        std::unique_ptr<ImageButtonNode> pauseButton = std::make_unique<ImageButtonNode>(
                            mWindow, this->mTexturesHolder[Textures::pauseButton], this->mTexturesHolder[Textures::pauseButtonHoverred],
                            sf::Vector2f(30, 30), sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30)/2, sf::VideoMode::getDesktopMode().height - 150)
                        );
                        mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(pauseButton);
                        mIsNext = 0;
                    }
                }
                break;
            }
            case 1: {
                if (child->getClickedIndex(event) == 0) {
                    if (!mIsActionPaused) {
                        std::unique_ptr<ImageButtonNode> playButton = std::make_unique<ImageButtonNode>(
                            mWindow, this->mTexturesHolder[Textures::playButton], this->mTexturesHolder[Textures::playButtonHoverred],
                            sf::Vector2f(30, 30), sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30)/2, sf::VideoMode::getDesktopMode().height - 150)
                        );
                        mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(playButton);
                    }
                    if (!mIsNext) mIsNext = 1;
                    mIsActionPaused = 0;
                }
                break;
            }
        }
        index++;
    }
}

void SettingsState::controlBoxUpdate() {
    if (mIsEndAnimation.first && !mIsEndAnimation.second) {
        std::unique_ptr<ImageButtonNode> replayButton = std::make_unique<ImageButtonNode>(
            mWindow, this->mTexturesHolder[Textures::replayButton], this->mTexturesHolder[Textures::replayButtonHoverred],
            sf::Vector2f(30, 30), sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30)/2, sf::VideoMode::getDesktopMode().height - 150)
        );
        mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(replayButton);
        mIsEndAnimation.second = 1;
    }

    if (mIsNext) {
        if (mPrevColorIndex != mColorIndex && mColorIndex != 0) {
            mPrevColorIndex = mColorIndex;
            mIsActionPaused = 1;
        } 
        if (mAnimationOrder != mPrevAnimationOrder) {
            mPrevAnimationOrder = mAnimationOrder;
            mIsActionPaused = 1;
        }
    }
}