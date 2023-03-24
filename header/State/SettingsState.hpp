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
    std::vector<bool> mStateActivated;
    std::vector<bool> mActionActivated;
    std::vector<int> mInputArr;
    int mActionIndex;
    int mInsertValue;
    bool mIsActionActivating = 0;
    void controlEvent(sf::Event &event);
private:
    enum Layers {
        Containers,
        DropBox,
        InputBox,
        ActionButtons,
        Error,
        LayerCount
    };
    sf::Clock clock;
    double elapsedTime;
    bool mIsEmerged;
private:
    virtual void loadTextures();
    virtual void loadFonts();
    virtual void buildScence();
private:
    void createRandomList();
    void throwError(const std::string &errorMessage);
    void settingsIn(sf::Time dt);
    void settingsOut(sf::Time dt);
    void handleAction(sf::Event &event);
    void handleActionDropBoxEvent(sf::Event &event);
};