#pragma once
#include <State/State.hpp>

class MenuState : public State {
public: 
    explicit MenuState(sf::RenderWindow &window);
    void handleMenuEvent(sf::Event &event);
    bool mIsProgramStarted = 0;
    bool mIsExit = 0;
private: 
    enum Layers {
        Background,
        Label,
        Buttons,
        LayerCount
    };
private:
    virtual void loadTextures();
    virtual void loadFonts();
    virtual void loadCode() {};
    virtual void buildScence();
};