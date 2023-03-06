#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Animation.h"
#include "DataStructure.h"

class LinkedList {
public:
    bool isInit;
    sf::Font ComfortaaRegular;
    sf::Font FiraSansRegular;
    void init(sf::RenderWindow &window);
    void addAnimation(sf::RenderWindow &window, std::vector<int> &arr, std::vector<GraphicalNode> &graphicalNode, std::vector<sf::Sprite> &arrowSprite, double &pos, int n, double &initialArrowLength, sf::Sprite &newArrowSprite, double &initialVal, int addIndex, double speed, bool &isInserted, bool &isInit, double &transitionVar, bool &isAnimation3Triggered);
};