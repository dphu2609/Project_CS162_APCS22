#pragma once

#include <State/State.hpp>

namespace States {
    enum ID {
        SinglyLinkedList,
        DoublyLinkedList,
        CircularLinkedList,
        StaticArray,
        DynamicArray,
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
    std::vector<bool> mStateActivated = {};
    std::vector<bool> mActionActivated = {};
    std::vector<int> mInputArr = {};
    int mActionIndex;
    int mActionValue;
    int mPrevActionValue;

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

    bool mIsReplay = 0;
    std::pair<bool, bool> mIsEndAnimation = {0, 0};
private:
    enum Layers {
        Containers,
        DropBox,
        InputBox,
        ActionButtons,
        Error,
        ControlBoxContainer,
        ControlBoxButtons,
        LayerCount
    };
    sf::Clock clock;
    double elapsedTime;
    bool mIsEmerged = 0;
    bool mIsControlBoxEmerged = 0;
private:
    virtual void loadTextures();
    virtual void loadFonts();
    virtual void loadCode() {};
    virtual void buildScence();
private:
    void createRandomList();
    void createRandomValue();
    void throwError(const std::string &errorMessage);
    void settingsIn(sf::Time dt);
    void settingsOut(sf::Time dt);
    void controlBoxOut(sf::Time dt);
    void controlBoxIn(sf::Time dt); 
    void handleAction(sf::Event &event);
    void handleActionDropBoxEvent(sf::Event &event);
    void handleControlBoxEvent(sf::Event &event);
};