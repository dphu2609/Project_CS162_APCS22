#include <State/SettingsState.hpp>

void SettingsState::handleDataDropBoxEvent(sf::Event &event) {
    for (auto &child : mSceneLayers[DataDropBox]->getChildren()) {
        int optionIndex = child->getClickedIndex(event);
        if (optionIndex == 0) {
            for (int i = 0; i < mStateActivated.size(); i++) {
                mStateActivated[i] = 0;
            }
            mFirstTimeVisited = 0;
            mSceneLayers[ActionDropBox]->getChildren().clear();
            mSceneLayers[InputBox]->getChildren().clear();
            mSceneLayers[ActionButtons]->getChildren().clear();
            mActionActivated[Action::ResetAction] = 1;
        } else if (optionIndex == States::Stack || optionIndex == States::Queue) {
            mSceneLayers[ActionDropBox]->getChildren().clear();
            std::vector<std::string> actionOptions = {"Create", "Push", "Pop"}; 
            std::unique_ptr<DropBoxNode> newActionDropBox = std::make_unique<DropBoxNode>(
                mWindow, "ACTION", actionOptions, mFontsHolder[Fonts::RobotoRegular],
                sf::Vector2f(180*Constant::scaleX, 50*Constant::scaleY), 0, 0, 
                sf::Vector2f(160*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 700*Constant::scaleY), 
                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255),
                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color::White,
                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
            );
            mSceneLayers[ActionDropBox]->attachChild(std::move(newActionDropBox));
        } else if (optionIndex == States::StaticArray || optionIndex == States::DynamicArray) {
            mSceneLayers[ActionDropBox]->getChildren().clear();
            std::vector<std::string> actionOptions = {"Create", "Insert", "Delete", "Update", "Search", "Access"}; 
            std::unique_ptr<DropBoxNode> newActionDropBox = std::make_unique<DropBoxNode>(
                mWindow, "ACTION", actionOptions, mFontsHolder[Fonts::RobotoRegular],
                sf::Vector2f(180*Constant::scaleX, 50*Constant::scaleY), 0, 0, 
                sf::Vector2f(160*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 700*Constant::scaleY), 
                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255),
                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color::White,
                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
            );
            mSceneLayers[ActionDropBox]->attachChild(std::move(newActionDropBox));
        }
         else if (optionIndex != -1) {
            mSceneLayers[ActionDropBox]->getChildren().clear();
            std::vector<std::string> actionOptions = {"Create", "Insert", "Delete", "Update", "Search"}; 
            std::unique_ptr<DropBoxNode> newActionDropBox = std::make_unique<DropBoxNode>(
                mWindow, "ACTION", actionOptions, mFontsHolder[Fonts::RobotoRegular],
                sf::Vector2f(180*Constant::scaleX, 50*Constant::scaleY), 0, 0, 
                sf::Vector2f(160*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 700*Constant::scaleY), 
                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255),
                sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color::White,
                sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
            );
            mSceneLayers[ActionDropBox]->attachChild(std::move(newActionDropBox));
        }
        if (optionIndex > 0) mStateActivated[optionIndex] = 1;
        break;
    }
}

void SettingsState::handleActionDropBoxEvent(sf::Event &event) {
    if (!mStateActivated[States::Stack] && !mStateActivated[States::Queue]) {
        for (auto &child : mSceneLayers[ActionDropBox]->getChildren()) {
            switch(child->getClickedIndex(event)) {
                case Action::Create : {
                    if (mSceneLayers[InputBox]->getChildren().size() == 0) {
                        std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
                            mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(300*Constant::scaleX, 40*Constant::scaleY), 2, 
                            sf::Vector2f(100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 480*Constant::scaleY), 
                            sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                        );
                        mSceneLayers[InputBox]->attachChild(std::move(newInputBox));

                        std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Random", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 600*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                        std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Custom input: ", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(180*Constant::scaleX, 45*Constant::scaleY), 0,
                            sf::Vector2f(100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 530*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                        std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                            mWindow, "GO", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(420*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 480*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton3));

                        std::unique_ptr<RectangleButtonNode> newButton4 = std::make_unique<RectangleButtonNode>(
                            mWindow, "LOAD FROM FILE", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(300*Constant::scaleX, 45*Constant::scaleY), 0,
                            sf::Vector2f(100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 380*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton4));

                        std::unique_ptr<RectangleButtonNode> newButton5 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Note: data is taken from\ndata/input.txt in the program folder.", mFontsHolder[Fonts::RobotoItalic], sf::Vector2f(180*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(200*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 300*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton5));

                        std::unique_ptr<RectangleButtonNode> newButton6 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Note: data must be in correct format.\nEx: -61 23 15 90", mFontsHolder[Fonts::RobotoItalic], sf::Vector2f(180*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(200*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 230*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton6));
                        createRandomList();
                        mActionActivated[Action::Create] = 1;
                    }
                    break;
                }
                case Action::Insert : {
                    if (mSceneLayers[InputBox]->getChildren().size() == 0) {
                        std::unique_ptr<InputBoxNode> newInputBox1 = std::make_unique<InputBoxNode>(
                            mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(120*Constant::scaleX, 40*Constant::scaleY), 2, 
                            sf::Vector2f(120*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 430*Constant::scaleY), 
                            sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                        );
                        mSceneLayers[InputBox]->attachChild(std::move(newInputBox1));

                        std::unique_ptr<InputBoxNode> newInputBox2 = std::make_unique<InputBoxNode>(
                            mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(120*Constant::scaleX, 40*Constant::scaleY), 2, 
                            sf::Vector2f(260*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 430*Constant::scaleY), 
                            sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                        );
                        mSceneLayers[InputBox]->attachChild(std::move(newInputBox2));

                        std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Insert Head", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 620*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                        std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Insert Tail", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 560*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                        std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Index", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(130*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 500*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton3));

                        std::unique_ptr<RectangleButtonNode> newButton4 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(130*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(250*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 500*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton4));

                        std::unique_ptr<RectangleButtonNode> newButton5 = std::make_unique<RectangleButtonNode>(
                            mWindow, "GO", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(420*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 430*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton5));
                        mActionActivated[Action::Insert] = 1;
                    }
                    break;
                }
                case Action::Delete : {
                    if (mSceneLayers[InputBox]->getChildren().size() == 0) {
                        std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
                            mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(250*Constant::scaleX, 40*Constant::scaleY), 2, 
                            sf::Vector2f(125*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 430*Constant::scaleY), 
                            sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                        );
                        mSceneLayers[InputBox]->attachChild(std::move(newInputBox));

                        std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Delete Head", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 620*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                        std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Delete Tail", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 560*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                        std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Custom Index", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 500*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton3));

                        std::unique_ptr<RectangleButtonNode> newButton4 = std::make_unique<RectangleButtonNode>(
                            mWindow, "GO", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(420*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 430*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton4));
                        mActionActivated[Action::Delete] = 1;
                    }
                    break;
                }
                case Action::Update : {
                    if (mSceneLayers[InputBox]->getChildren().size() == 0) {
                        std::unique_ptr<InputBoxNode> newInputBox1 = std::make_unique<InputBoxNode>(
                            mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(120*Constant::scaleX, 40*Constant::scaleY), 2, 
                            sf::Vector2f(120*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 550*Constant::scaleY), 
                            sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                        );
                        mSceneLayers[InputBox]->attachChild(std::move(newInputBox1));

                        std::unique_ptr<InputBoxNode> newInputBox2 = std::make_unique<InputBoxNode>(
                            mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(120*Constant::scaleX, 40*Constant::scaleY), 2, 
                            sf::Vector2f(260*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 550*Constant::scaleY), 
                            sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                        );
                        mSceneLayers[InputBox]->attachChild(std::move(newInputBox2));

                        std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Index", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(130*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 620*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                        std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(130*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(250*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 620*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                        std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                            mWindow, "GO", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(420*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 550*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton3));
                        mActionActivated[Action::Update] = 1;
                    }
                    break;
                }
                case Action::Search : {
                    if (mSceneLayers[InputBox]->getChildren().size() == 0) {
                        std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
                            mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(250*Constant::scaleX, 40*Constant::scaleY), 2, 
                            sf::Vector2f(125*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 480*Constant::scaleY), 
                            sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                        );
                        mSceneLayers[InputBox]->attachChild(std::move(newInputBox));

                        std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Random Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 600*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                        std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Custom Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 540*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                        std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                            mWindow, "GO", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(420*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 480*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton3));
                        mActionActivated[Action::Search] = 1;
                    }
                    break;
                }
                case Action::Access : {
                    if (mSceneLayers[InputBox]->getChildren().size() == 0) {
                        std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
                            mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(250*Constant::scaleX, 40*Constant::scaleY), 2, 
                            sf::Vector2f(125*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 430*Constant::scaleY), 
                            sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                        );
                        mSceneLayers[InputBox]->attachChild(std::move(newInputBox));

                        std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Index", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 500*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                        std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                            mWindow, "GO", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(420*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 430*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));
                        mActionActivated[Action::Access] = 1;
                    }
                    break;
                }
                case Action::ResetAction : {
                    mSceneLayers[InputBox]->getChildren().clear();
                    mSceneLayers[ActionButtons]->getChildren().clear();
                    for (int i = 0; i < mActionActivated.size(); i++) {
                        mActionActivated[i] = 0;
                    }
                    mActionActivated[Action::ResetAction] = 1;
                    break;
                }
            }
        }
    } else {
        for (auto &child : mSceneLayers[ActionDropBox]->getChildren()) {
            switch(child->getClickedIndex(event)) {
                case Action::Create : {
                    if (mSceneLayers[InputBox]->getChildren().size() == 0) {
                        std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
                            mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(300*Constant::scaleX, 40*Constant::scaleY), 2, 
                            sf::Vector2f(100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 480*Constant::scaleY), 
                            sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                        );
                        mSceneLayers[InputBox]->attachChild(std::move(newInputBox));

                        std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Random", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(110*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 600*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                        std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Custom input: ", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(180*Constant::scaleX, 45*Constant::scaleY), 0,
                            sf::Vector2f(100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 530*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                        std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                            mWindow, "GO", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(420*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 480*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton3));

                        std::unique_ptr<RectangleButtonNode> newButton4 = std::make_unique<RectangleButtonNode>(
                            mWindow, "LOAD FROM FILE", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(300*Constant::scaleX, 45*Constant::scaleY), 0,
                            sf::Vector2f(100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 380*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton4));

                        std::unique_ptr<RectangleButtonNode> newButton5 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Note: data is taken from\ndata/input.txt in the program folder.", mFontsHolder[Fonts::RobotoItalic], sf::Vector2f(180*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(200*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 300*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton5));

                        std::unique_ptr<RectangleButtonNode> newButton6 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Note: data must be in correct format.\nEx: -61 23 15 90", mFontsHolder[Fonts::RobotoItalic], sf::Vector2f(180*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(200*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 230*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton6));
                        createRandomList();
                        mActionActivated[Action::Create] = 1;
                    }
                    break;
                }
                case Action::Insert : {
                    if (mSceneLayers[InputBox]->getChildren().size() == 0) {
                        std::unique_ptr<InputBoxNode> newInputBox = std::make_unique<InputBoxNode>(
                            mWindow, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(250*Constant::scaleX, 40*Constant::scaleY), 2, 
                            sf::Vector2f(125*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 430*Constant::scaleY), 
                            sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Green
                        );
                        mSceneLayers[InputBox]->attachChild(std::move(newInputBox));

                        std::unique_ptr<RectangleButtonNode> newButton1 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Random Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(280*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(120*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 560*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton1));

                        std::unique_ptr<RectangleButtonNode> newButton2 = std::make_unique<RectangleButtonNode>(
                            mWindow, "Value", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(130*Constant::scaleX, 50*Constant::scaleY), 0,
                            sf::Vector2f(180*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 500*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton2));

                        std::unique_ptr<RectangleButtonNode> newButton3 = std::make_unique<RectangleButtonNode>(
                            mWindow, "GO", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(420*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 430*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton3));
                        mActionActivated[Action::Insert] = 1;
                    }
                    break;
                }
                case Action::Delete : {
                    if (mSceneLayers[InputBox]->getChildren().size() == 0) {
                        std::unique_ptr<RectangleButtonNode> newButton = std::make_unique<RectangleButtonNode>(
                            mWindow, "GO", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(80*Constant::scaleX, 40*Constant::scaleY), 0,
                            sf::Vector2f(210*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 580*Constant::scaleY),
                            sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                            sf::Color::White, sf::Color(41, 58, 117, 255), sf::Color::White
                        );
                        mSceneLayers[ActionButtons]->attachChild(std::move(newButton));
                        mActionActivated[Action::Delete] = 1;
                    }
                    break;
                }
                case Action::ResetAction : {
                    mSceneLayers[InputBox]->getChildren().clear();
                    mSceneLayers[ActionButtons]->getChildren().clear();
                    mActionActivated[Action::ResetAction] = 0;
                    for (int i = 1; i < mActionActivated.size(); i++) {
                        mActionActivated[i] = 0;
                    }
                    mActionActivated[Action::ResetAction] = 1;
                    break;
                }
            }
        }
    }
}

void SettingsState::createRandomList() {
    srand((unsigned int)time(NULL));
    int size = rand() % 4 + 3;
    mInputArr.clear();
    for (int i = 0; i < size; i++) {
        int newRanNum = 1 + rand() % 99;
        mInputArr.push_back(newRanNum);
    }
    for (auto &child : mSceneLayers[InputBox]->getChildren()) {
        std::string str = "";
        for (int i = 0; i < mInputArr.size() - 1; i++) {
            str += std::to_string(mInputArr[i]) + ", ";
        }
        str += std::to_string(mInputArr.back());
        child->setContent(str);
        break;
    }
}

void SettingsState::createRandomValue() {
    srand((unsigned int)time(NULL));
    int val;
    for (int i = 0; i < 10; i++) {
        val = rand() % 100;
    }
    if (mSceneLayers[InputBox]->getChildren().size() == 1) {
        for (auto &child : mSceneLayers[InputBox]->getChildren()) {
            child->setContent(std::to_string(val));
            break;
        }
    } else if (mSceneLayers[InputBox]->getChildren().size() == 2) {
        int index = 0;
        for (auto &child : mSceneLayers[InputBox]->getChildren()) {
            if (index == 1) {
                child->setContent(std::to_string(val));
            }
            index++;
        }
    }
}

void SettingsState::throwError(const std::string &errorMessage) {
    mSceneLayers[Error]->getChildren().clear();
    std::unique_ptr<RectangleButtonNode> newError = std::make_unique<RectangleButtonNode>(
        mWindow, errorMessage, mFontsHolder[Fonts::RobotoRegular], 
        sf::Vector2f(errorMessage.size()*25*Constant::scaleX, 60*Constant::scaleY), 0,
        sf::Vector2f(
            (sf::VideoMode::getDesktopMode().width - errorMessage.size()*25*Constant::scaleX - 35*Constant::scaleX)/2, 
            (sf::VideoMode::getDesktopMode().height - 70*Constant::scaleY)/2 - 30*Constant::scaleY
        ),
        sf::Color(201, 52, 112, 255), sf::Color(52, 53, 59, 255), sf::Color::White,
        sf::Color(201, 52, 112, 255), sf::Color(41, 58, 117, 255), sf::Color::White
    );
    mSceneLayers[Error]->attachChild(std::move(newError));
}

void SettingsState::loadFromFile() {
    bool isValid = 1;
    std::ifstream fin;
    fin.open("data/input.txt");
    if (!fin.is_open()) {
        throwError("Error: input.txt not found! Please check whether it is deleted or renamed.");
    } else {
        while (!fin.eof()) {
            std::string str;
            std::getline(fin, str);
            for (int i = 0; i < str.size(); i++) {
                if (
                    !((str[i] >= '0' && str[i] <= '9') || (str[i] == '-') || (str[i] == ' ')) || 
                    (str[i] == '-' && (str[i + 1] < '0' && str[i + 1] > '9'))
                ) {
                    throwError("The data is not in the correct format, please try again.");
                    isValid = 0;
                    break;
                }
            }
            if (!isValid) break;
        }
    }
    fin.close();
    if (!isValid) return;
    fin.open("data/input.txt");
    if (!fin.is_open()) {
        throwError("Error: input.txt not found! Please check whether it is deleted or renamed.");
    } else {
        mInputArr.clear();
        int index = 0;
        while (!fin.eof()) {
            int x;
            fin >> x;
            mInputArr.push_back(x);
            if (mInputArr.size() > 10) {
                throwError("Sorry, the maximum size is 10.");
                isValid = 0;
                break;
            } else if (x > 99999 || x < -9999) {
                std::string str = "Sorry, value at index " + std::to_string(index) + "must be in range from -9999 to 99999.";
                throwError(str);
                isValid = 0;
                break;
            }
            index++;
        }
    }
    fin.close();
    if (mInputArr.size() > 0 && isValid) {
        mActionActivated[Action::Play] = 1;
        mIsReplay = 0;
    }
}

void SettingsState::handleAction(sf::Event &event) {
    int index = 0;
    for (int i = 1; i < Action::ActionCount; i++) {
        if (mActionActivated[i]) {
            index = i;
            break;
        }
    }
    if (!mStateActivated[States::Stack] && !mStateActivated[States::Queue]) {
        switch(index) {
            case Action::Create : {
                int btnIndex = 0;
                for (auto &child : mSceneLayers[ActionButtons]->getChildren()) {
                    switch (btnIndex) {
                        case 0 : {
                            if (child->getClickedIndex(event) == 0) {
                                createRandomList();
                            }
                            break;
                        }
                        case 2 : {
                             if (child->getClickedIndex(event) == 0) {
                                bool isValid = 1;
                                for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                    std::vector<int> tempVector = child->getIntArrayData();
                                    mInputArr = tempVector;
                                }
                                for (int i = 0; i < mInputArr.size(); i++) {
                                    if (mInputArr[i] > 99999 || mInputArr[i] < -9999) {
                                        throwError("Sorry, value must be in range from -9999 to 99999.");
                                        isValid = 0;
                                        break;
                                    }
                                }
                                if (mInputArr.size() <= 10 && mInputArr.size() > 0 && isValid) {
                                    mActionActivated[Action::Play] = 1;
                                    mIsReplay = 0;
                                }
                            }
                            break;
                        }
                        case 3: {
                            if (child->getClickedIndex(event) == 0) {
                                loadFromFile();
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
                                    child->setContent("0");
                                    break;
                                }
                            }
                            break;
                        }
                        case 1: {
                            if (child->getClickedIndex(event) == 0) {
                                mActionIndex = mInputArr.size();
                                for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                    child->setContent(std::to_string(mActionIndex));
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
                                } else if (dataInput[0] < -9999 || dataInput[0] > 99999) {
                                    throwError("Sorry, value must be in range from -9999 to 99999.");
                                } else {
                                    for (int i = 0; i < Action::ActionCount; i++) mActionActivated[i] = 0;
                                    mActionActivated[Action::Insert] = 1;
                                    mActionActivated[Action::Play] = 1;
                                    mActionIndex = indexInput[0];
                                    mActionValue = dataInput[0];
                                    mSceneLayers[Error]->getChildren().clear();
                                    mTypeOfAction = Action::Insert;
                                    mIsPrev = 0;
                                    mIsNext = 0;
                                    mIsActionPaused = 0;
                                    mIsReplay = 0;
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
                                    child->setContent("0");
                                    break;
                                }
                            }
                            break;
                        }
                        case 1: {
                            if (child->getClickedIndex(event) == 0) {
                                mActionIndex = mInputArr.size() - 1;
                                for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                    child->setContent(std::to_string(mActionIndex));
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
                                    if (mInputArr.size() == 0) message = "Error: List is empty! Cannot perform this action.";
                                    else message = "Error: Index must be in range from 0 to " + std::to_string(mInputArr.size() - 1) + "!";
                                    throwError(message);
                                } else if (mInputArr.size() == 0) {
                                    throwError("Error: List is empty! Can not perform this action.");
                                }
                                else {
                                    for (int i = 0; i < Action::ActionCount; i++) mActionActivated[i] = 0;
                                    mActionActivated[Action::Delete] = 1;
                                    mActionActivated[Action::Play] = 1;
                                    mActionIndex = indexInput[0];
                                    mActionValue = mInputArr[mActionIndex];
                                    mSceneLayers[Error]->getChildren().clear();
                                    mTypeOfAction = Action::Delete;
                                    mIsPrev = 0;
                                    mIsNext = 0;
                                    mIsActionPaused = 0;
                                    mIsReplay = 0;
                                }
                            }
                            break;
                        }
                    }
                    btnIndex++;
                }
                break;
            }

            case Action::Update: {
                int btnIndex = 0;
                for (auto &child : mSceneLayers[ActionButtons]->getChildren()) {
                    switch (btnIndex) {
                        case 2: {
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
                                } else if (indexInput[0] > mInputArr.size() - 1 || indexInput[0] < 0) {
                                    std::string message = "";
                                    if (mInputArr.size() == 0) message = "Error: List is empty! Cannot perform this action.";
                                    else message = "Error: Index must be in range from 0 to " + std::to_string(mInputArr.size() - 1) + "!";
                                    throwError(message);
                                } else if (dataInput.size() != 1) {
                                    throwError("Error: Invalid value!");
                                } else if (dataInput[0] < -9999 || dataInput[0] > 99999) {
                                    throwError("Sorry, value must be in range from -9999 to 99999.");
                                } else {
                                    for (int i = 0; i < Action::ActionCount; i++) mActionActivated[i] = 0;
                                    mActionActivated[Action::Update] = 1;
                                    mActionActivated[Action::Play] = 1;
                                    mTypeOfAction = Action::Update;
                                    mActionIndex = indexInput[0];
                                    mActionValue = dataInput[0];
                                    mPrevActionValue = mInputArr[mActionIndex];
                                    mSceneLayers[Error]->getChildren().clear();
                                    mIsPrev = 0;
                                    mIsNext = 0;
                                    mIsActionPaused = 0;
                                    mIsReplay = 0;
                                }
                            }
                            break;
                        }   
                    }
                    btnIndex++;
                }
                break;
            }

            case Action::Search: {
                int btnIndex = 0;
                for (auto &child : mSceneLayers[ActionButtons]->getChildren()) {
                    switch (btnIndex) {
                        case 0: {
                            if (child->getClickedIndex(event) == 0) {
                                createRandomValue();
                            }
                            break;
                        }
                        case 2: {
                            if (child->getClickedIndex(event) == 0) {
                                std::vector<int> dataInput;
                                for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                    dataInput = child->getIntArrayData();
                                } 
                                if (mInputArr.size() == 0) {
                                    throwError("Error: List is empty! Cannot perform this action.");
                                } else if (dataInput.size() != 1) {
                                    throwError("Error: Invalid value!");
                                } else if (dataInput[0] < -9999 || dataInput[0] > 99999) {
                                    throwError("Sorry, value must be in range from -9999 to 99999.");
                                } else {
                                    for (int i = 0; i < Action::ActionCount; i++) mActionActivated[i] = 0;
                                    mActionActivated[Action::Search] = 1;
                                    mActionActivated[Action::Play] = 1;
                                    mTypeOfAction = Action::Search;
                                    mActionValue = dataInput[0];
                                    mSceneLayers[Error]->getChildren().clear();
                                    mIsPrev = 0;
                                    mIsNext = 0;
                                    mIsActionPaused = 0;
                                    mIsReplay = 0;
                                }
                            }
                            break;
                        }   
                    }
                    btnIndex++;
                }
                break;
            }
            case Action::Access : {
                int btnIndex = 0;
                for (auto &child : mSceneLayers[ActionButtons]->getChildren()) {
                    switch (btnIndex) {
                        case 1: {
                            if (child->getClickedIndex(event) == 0) {
                                std::vector<int> indexInput;
                                int inputBoxIndex = 0;
                                for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                    indexInput = child->getIntArrayData();
                                } 
                                if (indexInput.size() != 1) {
                                    throwError("Error: Invalid index!");
                                } else if (indexInput[0] > mInputArr.size() - 1 || indexInput[0] < 0) {
                                    std::string message = "";
                                    if (mInputArr.size() == 0) message = "Error: List is empty! Cannot perform this action.";
                                    else message = "Error: Index must be in range from 0 to " + std::to_string(mInputArr.size() - 1) + "!";
                                    throwError(message);
                                } else {
                                    for (int i = 0; i < Action::ActionCount; i++) mActionActivated[i] = 0;
                                    mActionActivated[Action::Access] = 1;
                                    mActionActivated[Action::Play] = 1;
                                    mTypeOfAction = Action::Update;
                                    mActionIndex = indexInput[0];
                                    mActionValue = mInputArr[mActionIndex];
                                    mPrevActionValue = mInputArr[mActionIndex];
                                    mSceneLayers[Error]->getChildren().clear();
                                    mIsPrev = 0;
                                    mIsNext = 0;
                                    mIsActionPaused = 0;
                                    mIsReplay = 0;
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
    } else {
        switch(index) {
            case Action::Create : {
                int btnIndex = 0;
                for (auto &child : mSceneLayers[ActionButtons]->getChildren()) {
                    switch (btnIndex) {
                        case 0 : {
                            if (child->getClickedIndex(event) == 0) {
                                createRandomList();
                            }
                            break;
                        }
                        case 2 : {
                            if (child->getClickedIndex(event) == 0) {
                                bool isValid = 1;
                                for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                    std::vector<int> tempVector = child->getIntArrayData();
                                    mInputArr = tempVector;
                                }
                                for (int i = 0; i < mInputArr.size(); i++) {
                                    if (mInputArr[i] > 99999 || mInputArr[i] < -9999) {
                                        throwError("Sorry, value must be in range from -9999 to 99999.");
                                        isValid = 0;
                                        break;
                                    }
                                }
                                if (mInputArr.size() <= 10 && mInputArr.size() > 0 && isValid) {
                                    mActionActivated[Action::Play] = 1;
                                    mIsReplay = 0;
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
                                createRandomValue();
                            }
                            break;
                        }
                        case 2: {
                            if (child->getClickedIndex(event) == 0) {
                                std::vector<int> dataInput;
                                for (auto &child : mSceneLayers[InputBox]->getChildren()) {
                                    dataInput = child->getIntArrayData();
                                } 
                                if (dataInput.size() != 1) {
                                    throwError("Error: Invalid value!");
                                } else if (mInputArr.size() >= 10) {
                                    throwError("Sorry, the maximum size is 10.");
                                } else if (dataInput[0] < -9999 || dataInput[0] > 99999) {
                                    throwError("Sorry, value must be in range from -9999 to 99999.");
                                } else {
                                    for (int i = 0; i < Action::ActionCount; i++) mActionActivated[i] = 0;
                                    mActionActivated[Action::Insert] = 1;
                                    mActionActivated[Action::Play] = 1;
                                    if (mStateActivated[States::Stack])  mActionIndex = 0;
                                    else if (mStateActivated[States::Queue]) mActionIndex = mInputArr.size();
                                    mActionValue = dataInput[0];
                                    mSceneLayers[Error]->getChildren().clear();
                                    mTypeOfAction = Action::Insert;
                                    mIsPrev = 0;
                                    mIsNext = 0;
                                    mIsActionPaused = 0;
                                    mIsReplay = 0;
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
                for (auto &child : mSceneLayers[ActionButtons]->getChildren()) {
                    if (child->getClickedIndex(event) == 0) {
                        if (mInputArr.size() == 0) {
                            throwError("Error: List is empty! Can not perform this action.");
                        }
                        else {
                            for (int i = 0; i < Action::ActionCount; i++) mActionActivated[i] = 0;
                            mActionActivated[Action::Delete] = 1;
                            mActionActivated[Action::Play] = 1;
                            mActionIndex = 0;
                            mActionValue = mInputArr[mActionIndex];
                            mSceneLayers[Error]->getChildren().clear();
                            mTypeOfAction = Action::Delete;
                            mIsPrev = 0;
                            mIsNext = 0;
                            mIsActionPaused = 0;
                            mIsReplay = 0;
                        }
                    }
                }
                break;
            }
        }
    }
}

void SettingsState::handleControlBoxEvent(sf::Event &event) {
    int index = 0;
    if (mActionActivated[Action::Play] && !mActionActivated[Action::Create]) {
        if (!mIsControlBoxEmerged) {
            std::unique_ptr<ImageButtonNode> pauseButton = std::make_unique<ImageButtonNode>(
                mWindow, mTexturesHolder[Textures::pauseButton], mTexturesHolder[Textures::pauseButtonHoverred],
                sf::Vector2f(30*Constant::scaleX, 30*Constant::scaleX), 
                sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 - 100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 220*Constant::scaleY + 300*Constant::scaleY)
            );
            mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(pauseButton);
        }
        else {
            std::unique_ptr<ImageButtonNode> pauseButton = std::make_unique<ImageButtonNode>(
                mWindow, mTexturesHolder[Textures::pauseButton], mTexturesHolder[Textures::pauseButtonHoverred],
                sf::Vector2f(30*Constant::scaleX, 30*Constant::scaleX), 
                sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 - 100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 220*Constant::scaleY)
            );
            mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(pauseButton);
        }
    }
    if (mIsPrev && !mIsPrevButtonClicked) {
        std::unique_ptr<ImageButtonNode> playButton = std::make_unique<ImageButtonNode>(
            mWindow, mTexturesHolder[Textures::playButton], mTexturesHolder[Textures::playButtonHoverred],
            sf::Vector2f(30*Constant::scaleX, 30*Constant::scaleX), 
            sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 - 100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 220*Constant::scaleY)
        );
        mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(playButton);
        mIsPrevButtonClicked = 1;
    }
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
                                mInputArr.insert(mInputArr.begin() + mActionIndex, mActionValue);
                                break;
                            }
                            case Action::Update: {
                                mInputArr[mActionIndex] = mPrevActionValue;
                                break;
                            }
                        }
                        mActionActivated[Action::Play] = 1;
                        mIsReplay = 1;
                        mIsActionPaused = 1;
                        mIsEndAnimation.second = 0;
                        mIsEndAnimation.first = 0;
                        mIsActionPaused = 1;
                        mIsPrevButtonClicked = 0;
                    }
                    if (!mIsActionPaused) {
                        mIsActionPaused = 1;
                    }
                    else {
                        mIsActionPaused = 0;
                        if (!mIsPrev) {
                            mPrevPlay = 1;
                        }
                        mIsNext = 0;
                        mIsPrev = 0;
                        mIsPlay = 1;
                        mIsPrevButtonClicked = 0;
                    }
                    if (mIsActionPaused) {
                        std::unique_ptr<ImageButtonNode> playButton = std::make_unique<ImageButtonNode>(
                            mWindow, mTexturesHolder[Textures::playButton], mTexturesHolder[Textures::playButtonHoverred],
                            sf::Vector2f(30*Constant::scaleX, 30*Constant::scaleX), 
                            sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 - 100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 220*Constant::scaleY)
                        );
                        mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(playButton);
                    } else {
                        std::unique_ptr<ImageButtonNode> pauseButton = std::make_unique<ImageButtonNode>(
                            mWindow, mTexturesHolder[Textures::pauseButton], mTexturesHolder[Textures::pauseButtonHoverred],
                            sf::Vector2f(30*Constant::scaleX, 30*Constant::scaleX), 
                            sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 - 100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 220*Constant::scaleY)
                        );
                        mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(pauseButton);
                    }
                }
                break;
            }
            case 1: {
                if (child->getClickedIndex(event) == 0) {
                    if (!mIsActionPaused) {
                        std::unique_ptr<ImageButtonNode> playButton = std::make_unique<ImageButtonNode>(
                            mWindow, mTexturesHolder[Textures::playButton], mTexturesHolder[Textures::playButtonHoverred],
                            sf::Vector2f(30*Constant::scaleX, 30*Constant::scaleX), 
                            sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 - 100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 220*Constant::scaleY)
                        );
                        mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(playButton);
                    }
                    if (!mIsPrev) {
                        mPrevNext = 1;
                    }
                    mIsNext = 1;
                    mIsActionPaused = 0;
                    mIsPrev = 0;
                    mIsPlay = 0;
                }
                break;
            }
            case 2: {
                if (child->getClickedIndex(event) == 0) {
                    if (!mIsActionPaused) {
                        std::unique_ptr<ImageButtonNode> playButton = std::make_unique<ImageButtonNode>(
                            mWindow, mTexturesHolder[Textures::playButton], mTexturesHolder[Textures::playButtonHoverred],
                            sf::Vector2f(30*Constant::scaleX, 30*Constant::scaleX), 
                            sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 - 100*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 220*Constant::scaleY)
                        );
                        mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(playButton);
                    }
                    mIsPrev = 1;
                    mIsActionPaused = 0;
                    mIsNext = 0;
                    mIsPlay = 0;
                }
                break;
            }
        }
        index++;
    }
    for (auto &child : mSceneLayers[ControlBoxSpeedButton]->getChildren()) {
        if (child->getClickedIndex(event) == 0) {
            if (!mIsSpeedBoxEmerged) {
                std::unique_ptr<RectangleButtonNode> speed2x = std::make_unique<RectangleButtonNode>(
                    mWindow, "2", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(200*Constant::scaleX, 50*Constant::scaleY), 0,
                    sf::Vector2f(sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 15*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 320*Constant::scaleY)),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                    sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                );
                mSceneLayers[ControlBoxSpeedOptions]->attachChild(std::move(speed2x));

                std::unique_ptr<RectangleButtonNode> speed175x = std::make_unique<RectangleButtonNode>(
                    mWindow, "1.75", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(200*Constant::scaleX, 50*Constant::scaleY), 0,
                    sf::Vector2f(sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 15*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 370*Constant::scaleY)),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                    sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                );
                mSceneLayers[ControlBoxSpeedOptions]->attachChild(std::move(speed175x));

                std::unique_ptr<RectangleButtonNode> speed15x = std::make_unique<RectangleButtonNode>(
                    mWindow, "1.5", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(200*Constant::scaleX, 50*Constant::scaleY), 0,
                    sf::Vector2f(sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 15*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 420*Constant::scaleY)),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                    sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                );
                mSceneLayers[ControlBoxSpeedOptions]->attachChild(std::move(speed15x));

                std::unique_ptr<RectangleButtonNode> speed125x = std::make_unique<RectangleButtonNode>(
                    mWindow, "1.25", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(200*Constant::scaleX, 50*Constant::scaleY), 0,
                    sf::Vector2f(sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 15*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 470*Constant::scaleY)),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                    sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                );
                mSceneLayers[ControlBoxSpeedOptions]->attachChild(std::move(speed125x));

                std::unique_ptr<RectangleButtonNode> speed1x = std::make_unique<RectangleButtonNode>(
                    mWindow, "Normal", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(200*Constant::scaleX, 50*Constant::scaleY), 0,
                    sf::Vector2f(sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 15*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 520*Constant::scaleY)),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                    sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                );
                mSceneLayers[ControlBoxSpeedOptions]->attachChild(std::move(speed1x));

                std::unique_ptr<RectangleButtonNode> speed075x = std::make_unique<RectangleButtonNode>(
                    mWindow, "0.75", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(200*Constant::scaleX, 50*Constant::scaleY), 0,
                    sf::Vector2f(sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 15*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 570*Constant::scaleY)),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                    sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                );
                mSceneLayers[ControlBoxSpeedOptions]->attachChild(std::move(speed075x));

                std::unique_ptr<RectangleButtonNode> speed05x = std::make_unique<RectangleButtonNode>(
                    mWindow, "0.5", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(200*Constant::scaleX, 50*Constant::scaleY), 0,
                    sf::Vector2f(sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 15*Constant::scaleY, sf::VideoMode::getDesktopMode().height - 620*Constant::scaleY)),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                    sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                );
                mSceneLayers[ControlBoxSpeedOptions]->attachChild(std::move(speed05x));

                std::unique_ptr<RectangleButtonNode> speed025x = std::make_unique<RectangleButtonNode>(
                    mWindow, "0.25", mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(200*Constant::scaleX, 50*Constant::scaleY), 0,
                    sf::Vector2f(sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 15*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 670*Constant::scaleY)),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                    sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255)
                );
                mSceneLayers[ControlBoxSpeedOptions]->attachChild(std::move(speed025x));

                sf::Vector2f checkMarkPos;
                if (mSpeed == 2) checkMarkPos = sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 185*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 305*Constant::scaleY);
                else if (mSpeed == 1.75) checkMarkPos = sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 185*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 355*Constant::scaleY);
                else if (mSpeed == 1.5) checkMarkPos = sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 185*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 405*Constant::scaleY);
                else if (mSpeed == 1.25) checkMarkPos = sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 185*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 455*Constant::scaleY);
                else if (mSpeed == 1) checkMarkPos = sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 185*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 505*Constant::scaleY);
                else if (mSpeed == 0.75) checkMarkPos = sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 185*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 555*Constant::scaleY);
                else if (mSpeed == 0.5) checkMarkPos = sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 185*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 605*Constant::scaleY);
                else if (mSpeed == 0.25) checkMarkPos = sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 185*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 655*Constant::scaleY);

                std::unique_ptr<ImageButtonNode> checkMark = std::make_unique<ImageButtonNode>(
                    mWindow, mTexturesHolder[Textures::speedCheckMark], mTexturesHolder[Textures::speedCheckMark],
                    sf::Vector2f(20*Constant::scaleX, 20*Constant::scaleY), checkMarkPos
                );
                mSceneLayers[ControlBoxSpeedOptions]->attachChild(std::move(checkMark));

                mIsSpeedBoxEmerged = 1;
            } else {
                mSceneLayers[ControlBoxSpeedOptions]->getChildren().clear();
                mIsSpeedBoxEmerged = 0;
            }
        } 
    }
    if (mIsSpeedBoxEmerged) {
        int index = 0;
        for (auto &child : mSceneLayers[ControlBoxSpeedOptions]->getChildren()) {
            if (child->getClickedIndex(event) == 0) {
                mSceneLayers[ControlBoxSpeedOptions]->getChildren().clear();
                mSceneLayers[ControlBoxSpeedDisplay]->getChildren().clear();
                mIsSpeedBoxEmerged = 0;
                std::string speedDisplayContent;
                if (index == 0) {
                    mSpeed = 2;
                    speedDisplayContent = "2x";
                } else if (index == 1) {
                    mSpeed = 1.75;
                    speedDisplayContent = "1.75x";
                } else if (index == 2) {
                    mSpeed = 1.5;
                    speedDisplayContent = "1.5x";
                } else if (index == 3) {
                    mSpeed = 1.25;
                    speedDisplayContent = "1.25x";
                } else if (index == 4) {
                    mSpeed = 1;
                    speedDisplayContent = "Normal";
                } else if (index == 5) {
                    mSpeed = 0.75;
                    speedDisplayContent = "0.75x";
                } else if (index == 6) {
                    mSpeed = 0.5;
                    speedDisplayContent = "0.5x";
                } else if (index == 7) {
                    mSpeed = 0.25;
                    speedDisplayContent = "0.25x";
                }
                std::unique_ptr<RectangleButtonNode> speedDislay = std::make_unique<RectangleButtonNode>(
                    mWindow, speedDisplayContent, mFontsHolder[Fonts::RobotoRegular], sf::Vector2f(200*Constant::scaleX, 50*Constant::scaleY), 0,
                    sf::Vector2f(sf::Vector2f((sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 + 15*Constant::scaleX, sf::VideoMode::getDesktopMode().height - 180*Constant::scaleY)),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255)
                );
                mSceneLayers[ControlBoxSpeedDisplay]->attachChild(std::move(speedDislay));
                break;
            }
            index++;
        }
    }
}

void SettingsState::controlBoxUpdate() {
    if (mIsEndAnimation.first && !mIsEndAnimation.second && !mIsPrev) {
        std::unique_ptr<ImageButtonNode> replayButton = std::make_unique<ImageButtonNode>(
            mWindow, mTexturesHolder[Textures::replayButton], mTexturesHolder[Textures::replayButtonHoverred],
            sf::Vector2f(30*Constant::scaleX, 30*Constant::scaleY), 
            sf::Vector2f(
                (sf::VideoMode::getDesktopMode().width - 30*Constant::scaleX)/2 - 100*Constant::scaleX, 
                sf::VideoMode::getDesktopMode().height - 220*Constant::scaleY
            )
        );
        mSceneLayers[ControlBoxButtons]->getChildren()[0] = std::move(replayButton);
        mIsEndAnimation.second = 1;
    }
}

void SettingsState::handleDarkModeEvent(sf::Event &event) {
    for (auto &child : mSceneLayers[DarkModeButton]->getChildren()) {
        if (child->getClickedIndex(event) == 0) {
            if (!mDarkMode) {
                mDarkMode = 1;
                std::unique_ptr<RectangleButtonNode> darkModeButton = std::make_unique<RectangleButtonNode>(
                    mWindow, "LIGHT MODE", mFontsHolder[Fonts::RobotoRegular],
                    sf::Vector2f(300*Constant::scaleX, 50*Constant::scaleY), 0, sf::Vector2f(100*Constant::scaleX, 700*Constant::scaleY),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                    sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255) 
                );
                mSceneLayers[DarkModeButton]->getChildren()[0] = std::move(darkModeButton);
            } else {
                mDarkMode = 0;
                std::unique_ptr<RectangleButtonNode> darkModeButton = std::make_unique<RectangleButtonNode>(
                    mWindow, "DARK MODE", mFontsHolder[Fonts::RobotoRegular],
                    sf::Vector2f(300*Constant::scaleX, 50*Constant::scaleY), 0, sf::Vector2f(100*Constant::scaleX, 700*Constant::scaleY),
                    sf::Color::White, sf::Color(52, 53, 59, 255), sf::Color(41, 58, 117, 255),
                    sf::Color::White, sf::Color(85, 93, 120, 255), sf::Color(41, 58, 117, 255) 
                );
                mSceneLayers[DarkModeButton]->getChildren()[0] = std::move(darkModeButton);
            }
        }
    }
}