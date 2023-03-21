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

class SettingsState : public State {
public:
    explicit SettingsState(sf::RenderWindow &window);
    void activeSettings(sf::Time dt);
    std::vector<bool> mIsStateActivated;
    void handleClick(sf::Event &event);
private:
    enum Layers {
        Containers,
        DropBox,
        InputBox,
        LayerCount
    };
    sf::Clock clock;
    double elapsedTime;
    bool mIsEmerged;
private:
    virtual void loadTextures();
    virtual void loadFonts();
    virtual void buildScence();
};