#include "../header/LinkedList.h"


void initHandle(bool isInit, bool &isOdd, int &timeIndex, int delayTime, int &nodeSize, int &arrowSize, int arrSize) {
    if (isInit) {
        timeIndex++;
        if (timeIndex > delayTime) {
            timeIndex = 0;
            if (isOdd) {
                arrowSize++;
                isOdd = 0;
            } else {
                nodeSize++;
                isOdd = 1;
            }
            if (nodeSize >= arrSize) nodeSize = arrSize;
            if (arrowSize >= arrSize - 1) arrowSize = arrSize - 1;
        }
    }
}

void LinkedList::addAnimation(sf::RenderWindow &window, std::vector<int> &arr, std::vector<GraphicalNode> &graphicalNode, std::vector<AnimationVar> &addVar,  std::vector<sf::Sprite> &arrowSprite, int &arrSize, int addIndex, double speed) {
    if (addVar[1].initialVar >= 0) { //animation 1
        addVar[1].initialVar -= 0.025*speed;
        newNode.set("12", FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + (addIndex)*250, std::pow(addVar[1].initialVar, 4) + 500, sf::Color::Black, sf::Color::White, anm::lightBlue);
    }
    else if (addVar[2].initialVar >= 0) { //animation 2
        newArrowSprite.setRotation(-90);
        newArrowSprite.setPosition(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex)*250 + 35, 500);
        newArrowSprite.setScale((-std::pow(addVar[2].initialVar, 2) + 120) / newArrowSprite.getLocalBounds().width, 50 / newArrowSprite.getLocalBounds().height);
        addVar[2].initialVar -= (std::sqrt(115)/80)*speed;
        addVar[2].isTriggered = 1;
    }
    else if (addVar[3].initialVar >= 0 && !addVar[3].isTriggered) { //animation 3
        double initialLength = 110;
        double initialAngle = -std::pow(addVar[3].initialVar, 4) + 66.8;
        arrowSprite[addIndex - 1].setRotation(initialAngle);
        float temp = initialAngle*(std::atan(1)*4)/180;
        arrowSprite[addIndex - 1].setScale(sf::Vector2f((initialLength/std::cos(temp)) / newArrowSprite.getLocalBounds().width, 50 / newArrowSprite.getLocalBounds().height));
        arrowSprite[addIndex - 1].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex-1)*250 + 130 + initialAngle*0.32934131737, 285 + initialAngle*0.19461077844);
        addVar[3].initialVar -= (std::sqrt(std::sqrt(66.8))/100)*speed;
    }
    else if (!addVar[4].isTriggered) {
        //animation 4.1
        if (addVar[3].initialVar <= 0 && !addVar[3].isTriggered) {
            addVar[3].initialVar = std::sqrt(std::sqrt(66.8));
            addVar[3].isTriggered = 1;
        }
        //----
        //animation 4.2
        if (addVar[3].initialVar >= 0) {
            double initialLength = 110;
            double initialAngle = std::pow(addVar[3].initialVar, 4);
            arrowSprite[addIndex - 1].setRotation(initialAngle);
            float temp = initialAngle*(std::atan(1)*4)/180;
            arrowSprite[addIndex - 1].setScale(sf::Vector2f((initialLength/std::cos(temp)) / newArrowSprite.getLocalBounds().width, 50 / newArrowSprite.getLocalBounds().height));
            arrowSprite[addIndex - 1].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex-1)*250 + 130 + initialAngle*0.32934131737, 285 + initialAngle*0.19461077844);
            addVar[3].initialVar -= (std::sqrt(std::sqrt(66.8))/110)*speed;
        }
        //-------------------
        //animation 4.3
        if (addVar[4].initialVar >= 0) {
            for (int i = addIndex; i < arrSize; i++) {
                std::string str = std::to_string(arr[i]);
                graphicalNode[i].set(str, FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + i*250 - std::pow(addVar[4].initialVar, 2) + 250, 250, sf::Color::Black, sf::Color::White, anm::lightBlue);
            }
            for (int i = addIndex; i < arrSize - 1; i++) {
                arrowSprite[i].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130 - std::pow(addVar[4].initialVar, 2) + 250, 285);
            }
            addVar[4].initialVar -= (std::sqrt(250)/100)*speed;
        }
        //---------------------
        //animation 4.4
        if (addVar[5].initialVar >= 0) {
            newNode.set("12", FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + addIndex*250, std::pow(addVar[5].initialVar, 4) + 250, sf::Color::Black, sf::Color::White, anm::lightBlue);
            addVar[5].initialVar -= (std::sqrt(std::sqrt(250))/100)*speed;
        }
        //-----------------------------------------------------
        
        //animation 4.5
        if (addVar[6].initialVar >= 0) {
            newArrowSprite.setRotation(-std::pow(addVar[6].initialVar, 4));
            addVar[6].initialVar -= (std::sqrt(std::sqrt(90))/110)*speed;
        }
        newArrowSprite.setPosition(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex)*250 + 35 + -std::pow(addVar[7].initialVar, 4) + 95, 285 + std::pow(addVar[8].initialVar, 4));
        newArrowSprite.setScale(110 / newArrowSprite.getLocalBounds().width, 50 / newArrowSprite.getLocalBounds().height);
        if (addVar[7].initialVar >= 0) addVar[7].initialVar -= (std::sqrt(std::sqrt(95))/200)*speed;
        if (addVar[8].initialVar >= 0) addVar[8].initialVar -= (std::sqrt(std::sqrt(215))/100)*speed;
        //-----------------------------
        for (int i = 0; i < arrSize; i++) {
            window.draw(graphicalNode[i].box);
            window.draw(graphicalNode[i].number);
        }
        for (int i = 0; i < arrSize - 1; i++) {
            window.draw(arrowSprite[i]);
        }
        if (addVar[3].initialVar < 0 && addVar[4].initialVar < 0 && addVar[5].initialVar < 0 && addVar[6].initialVar < 0 && addVar[7].initialVar < 0 && addVar[8].initialVar) {
            addVar[4].isTriggered = 1;
            isInit = 1;
        }
        else isInit = 0;
    }
    else if (!addVar[9].isTriggered) {
        if (!addVar[8].isTriggered) {
            graphicalNode.insert(graphicalNode.begin() + addIndex, newNode);
            arr.insert(arr.begin() + addIndex, 12);
            arrowSprite.insert(arrowSprite.begin() + addIndex - 1, arrowSprite[0]);
            for (int i = 0; i < arrSize + 1; i++) {
                arrowSprite[i].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130, 285);
            }
            arrSize++;
            addVar[8].isTriggered = 1;
        }
        else if (arrSize%2 == 0 && addVar[9].initialVar >= 0) {
            isInit = 0;
            for (int i = 0; i < arrSize; i++) {
                std::string str = std::to_string(arr[i]);
                graphicalNode[i].set(str, FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + i*250 + std::pow(addVar[9].initialVar, 2), 250, sf::Color::Black, sf::Color::White, anm::lightBlue);
            }
            for (int i = 0; i < arrSize - 1; i++) {
                arrowSprite[i].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130 + std::pow(addVar[9].initialVar, 2), 285);
            }
            addVar[9].initialVar -= (std::sqrt(250)/150);
        }
        else {
            isAdd = 0;
            isInit = 1;
            addVar[9].isTriggered = 1;
        }
        for (int i = 0; i < arrSize; i++) {
            window.draw(graphicalNode[i].box);
            window.draw(graphicalNode[i].number);
        }
        for (int i = 0; i < arrSize - 1; i++) {
            window.draw(arrowSprite[i]);
        }

    }
    if (!addVar[8].isTriggered) {
        window.draw(newNode.box);
        window.draw(newNode.number);
    }
    if (addVar[2].isTriggered && !addVar[8].isTriggered) window.draw(newArrowSprite);
}


void LinkedList::init(sf::RenderWindow &window) {
    window.setVerticalSyncEnabled(1);
    //Page setup
    if (!ComfortaaRegular.loadFromFile("fonts/Comfortaa-Regular.ttf")) {
        std::cout << "Error when loading font Comfortaa-Regular\n";
    }
    if (!FiraSansRegular.loadFromFile("fonts/FiraSans-Regular.ttf")) {
        std::cout << "Error when loading font FiraSans-Regular\n";
    }

    sf::Vector2i localPosition;
    sf::Text createButton;
    anm::setText(createButton, ComfortaaRegular, "Create", 100, 10, anm::maxHeight - 800, anm::whiteBlue);
    sf::Text addButton;
    anm::setText(addButton, ComfortaaRegular, "Add", 100, 10, anm::maxHeight - 400, anm::whiteBlue);
    //------------------------

    //----------------------
    sf::Texture arrowTexture;
    if (!arrowTexture.loadFromFile("img/rightArrow.png"));
    std::vector<sf::Sprite> arrowSprite(15);
    for (int i = 0; i < 15; i++) {
        arrowSprite[i].setTexture(arrowTexture);
    }
    //------------------------------

    std::vector arr = {-1, 10, 20000, -5, 78, 1310, -99};
    int arrSize = arr.size();

    std::vector<GraphicalNode> graphicalNode(15);

    //Init variable for effect
    int nodeSize = 0;
    int arrowSize = 0;
    int delayTime = 10;
    int timeIndex = 0;
    bool isOdd = 0;
    //---------------------------

    //Add variable
    std::vector<AnimationVar> addVar(15);
    int addIndex = 2;
    GraphicalNode newNode;
    newArrowSprite.setTexture(arrowTexture);
    //-----------------

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            localPosition = sf::Mouse::getPosition(window);
            //Hover
            anm::hoverText(createButton, localPosition, anm::lightBlue, anm::whiteBlue);
            anm::hoverText(addButton, localPosition, anm::lightBlue, anm::whiteBlue);
            //--------------------------------------------------------------------------

            //Init triggered
            if (anm::isHover(createButton, localPosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {      
                for (int i = 0; i < arrSize; i++) {
                    std::string str = std::to_string(arr[i]);
                    graphicalNode[i].set(str, FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + i*250, 250, sf::Color::Black, sf::Color::White, anm::lightBlue);
                    arrowSprite[i].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130, 285);
                    arrowSprite[i].setRotation(0);
                    arrowSprite[i].setScale(sf::Vector2f(110 / arrowSprite[0].getLocalBounds().width, 50 / arrowSprite[0].getLocalBounds().height));
                }
                isInit = 1;
                nodeSize = 0;
                arrowSize = 0;
                isOdd = 0;
            }
            //-------------------------------------------

            //Add triggered
            if (anm::isHover(addButton, localPosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                isAdd = 1;
                if (!addAgain) addAgain = 1;
                else if (addVar[8].isTriggered) {
                    arr.erase(arr.begin() + addIndex);
                    graphicalNode.erase(graphicalNode.begin() + addIndex);
                    arrowSprite.erase(arrowSprite.begin() + addIndex - 1);
                    arrSize--;
                    nodeSize--;
                    arrowSize--;
                }
                addVar[1].initialVar = std::sqrt(std::sqrt(400));
                addVar[2].initialVar = std::sqrt(120);
                addVar[3].initialVar = std::sqrt(std::sqrt(66.8));
                addVar[4].initialVar = std::sqrt(250);
                addVar[5].initialVar = std::sqrt(std::sqrt(250));
                addVar[6].initialVar = std::sqrt(std::sqrt(90));
                addVar[7].initialVar = std::sqrt(std::sqrt(35));
                addVar[8].initialVar = std::sqrt(std::sqrt(250));
                addVar[9].initialVar = std::sqrt(250);
                for (int i = 1; i <= 14; i++) addVar[i].isTriggered = 0;
                for (int i = 0; i < arrSize; i++) {
                    std::string str = std::to_string(arr[i]);
                    graphicalNode[i].set(str, FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + i*250, 250, sf::Color::Black, sf::Color::White, anm::lightBlue);
                    arrowSprite[i].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130, 285);
                    arrowSprite[i].setRotation(0);
                    arrowSprite[i].setScale(sf::Vector2f(110 / arrowSprite[0].getLocalBounds().width, 50 / arrowSprite[0].getLocalBounds().height));
                }
            }
            //-------------------------------------------

            if (event.type == sf::Event::Closed) 
                window.close();
        }
        window.clear();  
        window.draw(createButton);
        window.draw(addButton);

        if (addVar[9].isTriggered) {
            nodeSize++;
            arrowSize++;
            addVar[9].isTriggered = 0;
        }

        if (isInit) {
            for (int i = 0; i < nodeSize; i++) {
                window.draw(graphicalNode[i].box);
                window.draw(graphicalNode[i].number);
            }
            for (int i = 0; i < arrowSize; i++) {
                window.draw(arrowSprite[i]);
            }
        }

        if (isAdd) addAnimation(window, arr, graphicalNode, addVar, arrowSprite, arrSize, addIndex, 2);
        window.display();

        //Init handle
        initHandle(isInit, isOdd, timeIndex, delayTime, nodeSize, arrowSize, arrSize);
        //---------------------------------------------------
    }
}