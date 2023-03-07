#include "../header/LinkedList.h"

void LinkedList::initTriggered(std::vector<GraphicalNode> &graphicalNode, std::vector<sf::Sprite> &arrowSprite, std::vector<int> arr, Pointer &pHead, sf::Sprite &pointerArrow) {
    const int arrSize = arr.size();
    for (int i = 0; i < arrSize; i++) {
        std::string str = std::to_string(arr[i]);
        graphicalNode[i].set(str, FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + i*250, 250, sf::Color::Black, sf::Color::White, anm::lightBlue);
        arrowSprite[i].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130, 285);
        arrowSprite[i].setRotation(0);
        arrowSprite[i].setScale(defaultArrowScale);
    }
    pHead.set("head", FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + 28, 80, sf::Color(22, 34, 41, 255), sf::Color(229, 184, 168, 255), sf::Color(168, 213, 229, 255));
    pointerArrow.setScale(95 / pointerArrow.getLocalBounds().width, 50 / pointerArrow.getLocalBounds().height);
    pointerArrow.setRotation(90);
    pointerArrow.setPosition(anm::maxWidth/2 - (arrSize/2)*250 + 85, 145);
}

void LinkedList::addTriggered(std::vector<GraphicalNode> &graphicalNode, std::vector<AnimationVar> &addVar,  std::vector<sf::Sprite> &arrowSprite, std::vector<int> arr) {
    const int arrSize = arr.size();
    addVar[1].initialVar = std::sqrt(std::sqrt(400));
    addVar[2].initialVar = std::sqrt(120);
    addVar[3].initialVar = std::sqrt(std::sqrt(66.8));
    addVar[4].initialVar = std::sqrt(250);
    addVar[5].initialVar = std::sqrt(std::sqrt(250));
    addVar[6].initialVar = std::sqrt(std::sqrt(90));
    addVar[7].initialVar = std::sqrt(std::sqrt(35));
    addVar[8].initialVar = std::sqrt(std::sqrt(250));
    addVar[9].initialVar = std::sqrt(std::sqrt(69.19320899)); 
    addVar[10].initialVar = std::sqrt(std::sqrt(250));
    addVar[11].initialVar = std::sqrt(std::sqrt(69.19320899)); 
    addVar[12].initialVar = std::sqrt(250);
    addVar[13].initialVar = std::sqrt(std::sqrt(110/std::cos(66.8*std::atan(1)*4/180)));
    for (int i = 1; i <= 15; i++) addVar[i].isTriggered = 0;
    for (int i = 0; i < arrSize; i++) {
        std::string str = std::to_string(arr[i]);
        graphicalNode[i].set(str, FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + i*250, 250, sf::Color::Black, sf::Color::White, anm::lightBlue);
        arrowSprite[i].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130, 285);
        arrowSprite[i].setRotation(0);
        arrowSprite[i].setScale(defaultArrowScale);
    }
}

void LinkedList::addAnimation(sf::RenderWindow &window, 
                              std::vector<int> &arr, 
                              std::vector<GraphicalNode> &graphicalNode,
                              Pointer &pHead, sf::Sprite &pointerArrow, 
                              std::vector<AnimationVar> &addVar, 
                              std::vector<sf::Sprite> &arrowSprite, 
                              int &arrSize, int addIndex, int addValue, double speed) 
{
    std::string str = std::to_string(addValue);
    if (addVar[1].initialVar >= 0) { //animation 1
        sf::Vector2f newPos(
            anm::maxWidth/2 - (arrSize/2)*250 + (addIndex)*250, 
            std::pow(addVar[1].initialVar, 4) + 500
        );
        addVar[1].initialVar -= 0.025*speed;
        newNode.set(str, FiraSansRegular, newPos.x, newPos.y, sf::Color::Black, sf::Color::White, anm::lightBlue);
    }
    else if (addVar[2].initialVar >= 0 && addIndex != arrSize && !addVar[3].isTriggered) { //animation 2
        sf::Vector2f newScale(
            (-std::pow(addVar[2].initialVar, 2) + 120) / newArrowSprite.getLocalBounds().width, 
            50 / newArrowSprite.getLocalBounds().height
        );
        sf::Vector2f newPos(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex)*250 + 35, 500);
        newArrowSprite.setRotation(-90);
        newArrowSprite.setPosition(newPos);
        newArrowSprite.setScale(newScale);
        addVar[2].initialVar -= (std::sqrt(115)/80)*speed;
        addVar[2].isTriggered = 1;
    }
    else if (addVar[3].initialVar >= 0 && !addVar[3].isTriggered && addIndex != 0) { //animation 3
        if (addIndex != arrSize) {
            double angleDegree = -std::pow(addVar[3].initialVar, 4) + 66.8;
            double angleRadian = angleDegree*(std::atan(1)*4)/180;
            sf::Vector2f newScale(
                (110/std::cos(angleRadian)) / newArrowSprite.getLocalBounds().width, 
                50 / newArrowSprite.getLocalBounds().height
            );
            sf::Vector2f newPos(
                anm::maxWidth/2 - (arrSize/2)*250 + (addIndex-1)*250 + 130 + angleDegree*0.32934131737, 
                285 + angleDegree*0.19461077844
            );
            arrowSprite[addIndex - 1].setRotation(angleDegree);
            arrowSprite[addIndex - 1].setScale(newScale);
            arrowSprite[addIndex - 1].setPosition(newPos);
            addVar[3].initialVar -= (std::sqrt(std::sqrt(66.8))/100)*speed;
        } else {
            double angleDegree = 66.8;
            sf::Vector2f newScale(
                ((-std::pow(addVar[13].initialVar, 4) +  279.2289861))/ newArrowSprite.getLocalBounds().width, 
                50 / newArrowSprite.getLocalBounds().height
            );
            sf::Vector2f newPos(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex-1)*250 + 150, 295);
            arrowSprite[addIndex - 1].setRotation(66.8);
            arrowSprite[addIndex - 1].setScale(newScale);
            arrowSprite[addIndex - 1].setPosition(newPos);
            window.draw(arrowSprite[addIndex - 1]);
            if (addVar[13].initialVar >= 0) addVar[13].initialVar -= (std::sqrt(std::sqrt(110/std::cos(66.8*std::atan(1)*4/180)))/200)*speed;
            else addVar[3].initialVar = -1;
        }
    }
    else if (!addVar[4].isTriggered) {
        //animation 4.1
        if ((addVar[3].initialVar <= 0) && !addVar[3].isTriggered) {
            addVar[3].initialVar = std::sqrt(std::sqrt(66.8));
            addVar[3].isTriggered = 1;
        }
        //----
        //animation 4.2
        if (addVar[3].initialVar >= 0 && addIndex != 0) {
            double angleDegree = std::pow(addVar[3].initialVar, 4);
            double angleRadian = angleDegree*(std::atan(1)*4)/180;
            sf::Vector2f newScale(
                (110 / std::cos(angleRadian)) / newArrowSprite.getLocalBounds().width,
                50 / newArrowSprite.getLocalBounds().height
            );
            sf::Vector2f newPos(
                anm::maxWidth/2 - (arrSize/2)*250 + (addIndex-1)*250 + 130 + angleDegree*0.32934131737, 
                285 + angleDegree*0.19461077844
            );
            arrowSprite[addIndex - 1].setRotation(angleDegree);
            arrowSprite[addIndex - 1].setScale(newScale);
            arrowSprite[addIndex - 1].setPosition(newPos);
            addVar[3].initialVar -= (std::sqrt(std::sqrt(66.8))/110)*speed;
        }
        //-------------------
        //animation 4.3
        if (addVar[4].initialVar >= 0) {
            for (int i = addIndex; i < arrSize; i++) {
                std::string str = std::to_string(arr[i]);
                sf::Vector2f newPos(anm::maxWidth/2 - (arrSize/2)*250 + i*250 - std::pow(addVar[4].initialVar, 2) + 250, 250);
                graphicalNode[i].set(str, FiraSansRegular, newPos.x, newPos.y, sf::Color::Black, sf::Color::White, anm::lightBlue);
            }
            for (int i = addIndex; i < arrSize - 1; i++) {
                sf::Vector2f newPos(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130 - std::pow(addVar[4].initialVar, 2) + 250, 285);
                arrowSprite[i].setPosition(newPos);
            }
            if (addIndex == 0) {
                sf::Vector2f newHeadPos(anm::maxWidth/2 - (arrSize/2)*250 + 28 - std::pow(addVar[4].initialVar, 2) + 250, 80);
                sf::Vector2f newArrowPos(anm::maxWidth/2 - (arrSize/2)*250 + 85 - std::pow(addVar[4].initialVar, 2) + 250, 145);
                pHead.set("head", FiraSansRegular, newHeadPos.x, newHeadPos.y, sf::Color(22, 34, 41, 255), sf::Color(229, 184, 168, 255), sf::Color(168, 213, 229, 255));
                pointerArrow.setPosition(newArrowPos);
            }
            addVar[4].initialVar -= (std::sqrt(250)/100)*speed;
        }
        //---------------------
        //animation 4.4
        if (addVar[5].initialVar >= 0) {
            sf::Vector2f newPos(
                anm::maxWidth/2 - (arrSize/2)*250 + addIndex*250, 
                std::pow(addVar[5].initialVar, 4) + 250
            );
            newNode.set(str, FiraSansRegular, newPos.x, newPos.y , sf::Color::Black, sf::Color::White, anm::lightBlue);
            addVar[5].initialVar -= (std::sqrt(std::sqrt(250))/100)*speed;
        }
        else addVar[5].isTriggered = 1;
        //-----------------------------------------------------
        
        //animation 4.5
        if (addVar[6].initialVar >= 0) {
            newArrowSprite.setRotation(-std::pow(addVar[6].initialVar, 4));
            addVar[6].initialVar -= (std::sqrt(std::sqrt(90))/110)*speed;
        }
        else addVar[6].isTriggered = 1;
        newArrowSprite.setPosition(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex)*250 + 35 + -std::pow(addVar[7].initialVar, 4) + 95, 285 + std::pow(addVar[8].initialVar, 4));
        newArrowSprite.setScale(defaultArrowScale);
        if (addVar[7].initialVar >= 0) addVar[7].initialVar -= (std::sqrt(std::sqrt(95))/200)*speed;
        else addVar[7].isTriggered = 1;
        if (addVar[8].initialVar >= 0) addVar[8].initialVar -= (std::sqrt(std::sqrt(215))/100)*speed;
        //-----------------------------
        for (int i = 0; i < arrSize; i++) {
            window.draw(graphicalNode[i].box);
            window.draw(graphicalNode[i].number);
        }
        for (int i = 0; i < arrSize - 1; i++) {
            window.draw(arrowSprite[i]);
        }
        if (addVar[5].isTriggered && addVar[6].isTriggered && addVar[7].isTriggered) {
            addVar[4].isTriggered = 1;
            isInit = 1;
        }
        else isInit = 0;

        if (addIndex == arrSize) window.draw(arrowSprite[addIndex - 1]);
    }
    else if (!addVar[9].isTriggered && addIndex == 0) {
        double angleDegree = -std::pow(addVar[9].initialVar, 4) + 69.19320899;
        double angleRadian = angleDegree*(std::atan(1)*4)/180;
        sf::Vector2f newScale(
            (95/std::cos(angleRadian)) / newArrowSprite.getLocalBounds().width, 
            50 / newArrowSprite.getLocalBounds().height
        );
        sf::Vector2f newPos(
            anm::maxWidth/2 - (arrSize/2)*250 + 85 - angleDegree*0.2 + 250, 
            145 + angleDegree*0.38
        );
        pointerArrow.setRotation(angleDegree + 90);
        pointerArrow.setScale(newScale);
        pointerArrow.setPosition(newPos);
        if (addVar[9].initialVar >= 0) addVar[9].initialVar -= (std::sqrt(std::sqrt(69.19320899))/100)*speed;
        else addVar[9].isTriggered = 1;
    }
    else if (!addVar[10].isTriggered && addIndex == 0) {
        sf::Vector2f newHeadPos(anm::maxWidth/2 - (arrSize/2)*250 + 28 + std::pow(addVar[10].initialVar, 4), 80);
        sf::Vector2f newArrowPos(anm::maxWidth/2 - (arrSize/2)*250 + 85 + std::pow(addVar[10].initialVar, 4), 145);
        pHead.set("head", FiraSansRegular, newHeadPos.x, newHeadPos.y, sf::Color(22, 34, 41, 255), sf::Color(229, 184, 168, 255), sf::Color(168, 213, 229, 255));
        pointerArrow.setPosition(newArrowPos);
        addVar[10].initialVar -= (std::sqrt(std::sqrt(250))/100)*speed;
        
        double angleDegree = std::pow(addVar[11].initialVar, 4);
        double angleRadian = angleDegree*(std::atan(1)*4)/180;
        sf::Vector2f newScale(
            (95/std::cos(angleRadian)) / newArrowSprite.getLocalBounds().width, 
            50 / newArrowSprite.getLocalBounds().height
        );
        sf::Vector2f newPos(
            anm::maxWidth/2 - (arrSize/2)*250 + 85 - angleDegree*0.2 + std::pow(addVar[10].initialVar, 4), 
            145 + angleDegree*0.38
        );
        pointerArrow.setRotation(angleDegree + 90);
        pointerArrow.setScale(newScale);
        pointerArrow.setPosition(newPos);
        if (addVar[11].initialVar >= 0) addVar[11].initialVar -= (std::sqrt(std::sqrt(69.19320899))/100)*speed;
        else addVar[11].isTriggered = 1;

        if (addVar[11].initialVar < 0 && addVar[10].initialVar < 0) 
            addVar[10].isTriggered = 1;

    }
    else if (!addVar[12].isTriggered) {
        if (!addVar[8].isTriggered) {
            graphicalNode.insert(graphicalNode.begin() + addIndex, newNode);
            arr.insert(arr.begin() + addIndex, addValue);
            if (addIndex != 0) arrowSprite.insert(arrowSprite.begin() + addIndex - 1, arrowSprite[0]);
            for (int i = 0; i < arrSize + 1; i++) {
                arrowSprite[i].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130, 285);
            }
            arrSize++;
            addVar[8].isTriggered = 1;
        }
        else if (arrSize%2 == 0 && addVar[12].initialVar >= 0) {
            isInit = 0;
            for (int i = 0; i < arrSize; i++) {
                std::string str = std::to_string(arr[i]);
                graphicalNode[i].set(str, FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + i*250 + std::pow(addVar[12].initialVar, 2), 250, sf::Color::Black, sf::Color::White, anm::lightBlue);
            }
            for (int i = 0; i < arrSize - 1; i++) {
                arrowSprite[i].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130 + std::pow(addVar[12].initialVar, 2), 285);
            }
            sf::Vector2f newHeadPos(anm::maxWidth/2 - (arrSize/2)*250 + 28 + std::pow(addVar[12].initialVar, 2), 80);
            sf::Vector2f newArrowPos(anm::maxWidth/2 - (arrSize/2)*250 + 85 + std::pow(addVar[12].initialVar, 2), 145);
            pHead.set("head", FiraSansRegular, newHeadPos.x, newHeadPos.y, sf::Color(22, 34, 41, 255), sf::Color(229, 184, 168, 255), sf::Color(168, 213, 229, 255));
            pointerArrow.setPosition(newArrowPos);
            addVar[12].initialVar -= (std::sqrt(250)/150);
        }
        else {
            isAdd = 0;
            isInit = 1;
            addVar[12].isTriggered = 1;
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
    window.draw(pHead.box);
    window.draw(pHead.text);
    window.draw(pointerArrow);
}


LinkedList::LinkedList(sf::RenderWindow &window) {
    //data
    std::vector<AnimationVar> addVar(20);
    std::vector<sf::Sprite> arrowSprite(20);
    std::vector<GraphicalNode> graphicalNode(15);
    std::vector arr = {-1, 10, 20000, -5, 78};
    Pointer pHead;
    sf::Sprite pointerArrow;
    int arrSize = arr.size();
    int addIndex = 5;
    //---------------------------

    //Font
    if (!ComfortaaRegular.loadFromFile("fonts/Comfortaa-Regular.ttf")) {
        std::cout << "Error when loading font Comfortaa-Regular\n";
    }
    if (!FiraSansRegular.loadFromFile("fonts/FiraSans-Regular.ttf")) {
        std::cout << "Error when loading font FiraSans-Regular\n";
    }
    //---------------------

    //Button
    sf::Text createButton;
    anm::setText(createButton, ComfortaaRegular, "Create", 100, 10, anm::maxHeight - 800, anm::whiteBlue);
    sf::Text addButton;
    anm::setText(addButton, ComfortaaRegular, "Add", 100, 10, anm::maxHeight - 400, anm::whiteBlue);
    //------------------------

    //Arrow setup
    sf::Texture arrowTexture;
    if (!arrowTexture.loadFromFile("img/rightArrow.png")) {
        std::cout << "Error when loading rightArrow.png\n";
    }
    for (int i = 0; i < 15; i++) {
        arrowSprite[i].setTexture(arrowTexture);
    }
    newArrowSprite.setTexture(arrowTexture);
    defaultArrowScale.x = 110 / arrowSprite[0].getLocalBounds().width;
    defaultArrowScale.y =  50 / arrowSprite[0].getLocalBounds().height;
    sf::Texture pointerArrowTexture;
    if (!pointerArrowTexture.loadFromFile("img/pointerArrow.png")) {
        std::cout << "Error when loading pointerArrow.png\n";
    }
    pointerArrow.setTexture(pointerArrowTexture);
    //---------------------------------------------------------------

    sf::Vector2i localPosition;
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
                isInit = 1;      
                initTriggered(graphicalNode, arrowSprite, arr, pHead, pointerArrow);
            }
            //-------------------------------------------

            //Add triggered
            if (anm::isHover(addButton, localPosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                isAdd = 1;
                addTriggered(graphicalNode, addVar, arrowSprite, arr);
            }
            //-------------------------------------------

            if (event.type == sf::Event::Closed) 
                window.close();
        }
        window.clear();  
        window.draw(createButton);
        window.draw(addButton);

        if (isInit) {
            for (int i = 0; i < arr.size(); i++) {
                window.draw(graphicalNode[i].box);
                window.draw(graphicalNode[i].number);
            }
            for (int i = 0; i < arr.size() - 1; i++) {
                window.draw(arrowSprite[i]);
            }
            if (!isAdd) {
                window.draw(pHead.box);
                window.draw(pHead.text);
                window.draw(pointerArrow);
            }
        }

        if (isAdd) addAnimation(window, arr, graphicalNode, pHead, pointerArrow, addVar, arrowSprite, arrSize, addIndex, -231, 1);
        window.display();
    }
}