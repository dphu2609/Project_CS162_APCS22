#include <State/State.hpp>

class SettingsState : public State {
public:
    explicit SettingsState(sf::RenderWindow &window);
    virtual void handleEvent();
    void activeSettings(sf::Time dt);
private:
    enum Layers {
        Containers,
        DropBox,
        DropBoxItems,
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