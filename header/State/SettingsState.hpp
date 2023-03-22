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
        ActionCount
    };
};

class SettingsState : public State {
public:
    explicit SettingsState(sf::RenderWindow &window);
    void activeSettings(sf::Time dt);
    std::vector<bool> mIsStateActivated;
    std::vector<bool> mActionActivated;
    void handleInput(sf::Event &event);
    std::vector<int> mInputArr;
    int mActionIndex;
    void handleAction(sf::Event &event);
private:
    enum Layers {
        Containers,
        DropBox,
        InputBox,
        ActionButtons,
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
};