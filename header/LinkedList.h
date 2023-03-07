#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Animation.h"
#include "DataStructure.h"

class LinkedList {
public:
    bool isInit = 0;
    bool isAdd = 0;
    bool addAgain = 0;
    sf::Sprite newArrowSprite;
    sf::Font ComfortaaRegular;
    sf::Font FiraSansRegular;
    sf::Vector2f defaultArrowScale;
    GraphicalNode newNode;
    LinkedList(sf::RenderWindow &window);
    void initTriggered(std::vector<GraphicalNode> &graphicalNode, std::vector<sf::Sprite> &arrowSprite, std::vector<int> arr);
    void addAnimation(sf::RenderWindow &window, std::vector<int> &arr, std::vector<GraphicalNode> &graphicalNode, std::vector<AnimationVar> &addVar,  std::vector<sf::Sprite> &arrowSprite, int &arrSize, int addIndex, double speed);
    void addTriggered(std::vector<GraphicalNode> &graphicalNode, std::vector<AnimationVar> &addVar,  std::vector<sf::Sprite> &arrowSprite, std::vector<int> arr);
};