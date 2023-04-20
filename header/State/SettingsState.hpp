#pragma once

#include <State/State.hpp>

namespace States {
    enum ID {
        None,
        StaticArray,
        DynamicArray,
        SinglyLinkedList,
        DoublyLinkedList,
        CircularLinkedList,
        Stack,
        Queue,
        StatesCount
    };
};

namespace Action {
    enum ID {
        ResetAction,
        Create,
        Insert,
        Delete,
        Update,
        Search,
        Play,
        ActionCount
    };
};

class SettingsState : public State {
public:
    explicit SettingsState(sf::RenderWindow &window);
    void activeSettings(sf::Time dt);
    void controlEvent(sf::Event &event);
    void controlBoxUpdate();
    //animation variables
    std::vector<bool> mStateActivated = {};
    std::vector<bool> mActionActivated = {};
    std::vector<int> mInputArr = {};    
    int mActionIndex;
    int mActionValue;
    int mPrevActionValue;
    //--------------------------------

    //control box variables
    int mTypeOfAction = 0;
    bool mIsActionPaused = 0;
    bool mIsPrev = 0;
    bool mIsNext = 0;
    bool mPrevNext = 0;
    bool mPrevPrev = 0;
    bool mPrevPlay = 0;
    bool mIsPlay = 0;
    int mPrevAnimationOrder = 1;
    int mAnimationOrder = 1;
    int mPrevColorIndex = 0;
    int mColorIndex = 0;
    std::pair<bool, bool> mIsEndAnimation = {0, 0};
    double mSpeed = 1;
    //--------------------------------

    bool mIsReplay = 0;
    bool mDarkMode = 1;
    bool mIsPrevButtonClicked = 0;
private:
    enum Layers {
        Containers,
        DataDropBox,
        ActionDropBox,
        StackQueueDropBox,
        InputBox,
        ActionButtons,
        DarkModeButton,
        Error,
        ControlBoxContainer,
        ControlBoxButtons,
        ControlBoxSpeedButton,
        ControlBoxSpeedOptions,
        ControlBoxSpeedDisplay,
        LayerCount
    };
    sf::Clock clock;
    double elapsedTime;
    bool mIsEmerged = 1;
    bool mIsControlBoxEmerged = 0;
    bool mFirstTimeVisited = 1;
    bool mIsSpeedBoxEmerged = 0;
private:
    virtual void loadTextures();
    virtual void loadFonts();
    virtual void loadCode() {};
    virtual void buildScence();
private:
    void createRandomList();
    void createRandomValue();
    void throwError(const std::string &errorMessage);
    void loadFromFile();
    void settingsIn(sf::Time dt);
    void settingsOut(sf::Time dt);
    void controlBoxOut(sf::Time dt);
    void controlBoxIn(sf::Time dt); 
    void handleDataDropBoxEvent(sf::Event &event);
    void handleActionDropBoxEvent(sf::Event &event);
    void handleAction(sf::Event &event);
    void handleControlBoxEvent(sf::Event &event);
    void handleDarkModeEvent(sf::Event &event);
};