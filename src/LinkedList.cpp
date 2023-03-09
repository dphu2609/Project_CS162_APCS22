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
    addVar[2].initialVar = std::sqrt(std::sqrt(120));
    addVar[3].initialVar = std::sqrt(std::sqrt(66.8));
    addVar[4].initialVar = std::sqrt(std::sqrt(250));
    addVar[5].initialVar = std::sqrt(std::sqrt(250));
    addVar[6].initialVar = std::sqrt(std::sqrt(90));
    addVar[7].initialVar = std::sqrt(std::sqrt(35));
    addVar[8].initialVar = std::sqrt(std::sqrt(250));
    addVar[9].initialVar = std::sqrt(std::sqrt(69.19320899)); 
    addVar[10].initialVar = std::sqrt(std::sqrt(250));
    addVar[11].initialVar = std::sqrt(std::sqrt(69.19320899)); 
    addVar[12].initialVar = std::sqrt(std::sqrt(250));
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

void LinkedList::addAnimation(sf::RenderWindow &window, int &addAnimationOrder,
                              std::vector<int> &arr, 
                              std::vector<GraphicalNode> &graphicalNode,
                              Pointer &pHead, sf::Sprite &pointerArrow, 
                              std::vector<AnimationVar> &addVar, 
                              std::vector<sf::Sprite> &arrowSprite, 
                              int &arrSize, int addIndex, int addValue, double speed) 
{
    std::string str = std::to_string(addValue);
    isInit = 0;
    if (!isPause) {
        switch(addAnimationOrder) {
        case 1: {
            sf::Vector2f newPos(
                anm::maxWidth/2 - (arrSize/2)*250 + (addIndex)*250, 
                addVar[1].backwardVal(500)
            );
            newNode.set(str, FiraSansRegular, newPos.x, newPos.y, sf::Color::Black, sf::Color::White, anm::lightBlue);
            if (addVar[1].initialVar >= 0) addVar[1].changeVar(500, 900, 100, speed);
            else addAnimationOrder = 2;
            break;
        }
        case 2: {
            if (addIndex == arrSize) {
                addAnimationOrder = 8;
                break;
            }
            sf::Vector2f newScale(
                addVar[2].forwardVal(0, 120) / newArrowSprite.getLocalBounds().width, 
                50 / newArrowSprite.getLocalBounds().height
            );
            sf::Vector2f newPos(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex)*250 + 35, 500);
            newArrowSprite.setRotation(-90);
            newArrowSprite.setPosition(newPos);
            newArrowSprite.setScale(newScale);
            if (addVar[2].initialVar >= 0) addVar[2].changeVar(0, 120, 80, speed);
            else addAnimationOrder = 3;
            addVar[2].isTriggered = 1;
            break;
        }
        case 3: {
            if (addIndex == 0) {
                addAnimationOrder = 4;
                break;
            }
            addVar[2].isTriggered = 1;
            double angleDegree = addVar[2].forwardVal(0, 66.8);
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
            if (addVar[3].initialVar >= 0) addVar[3].changeVar(0, 66.8, 100, speed);
            else addAnimationOrder = 4;
            break;
        }
        case 4: {
            //animation 4.1
            if ((addVar[3].initialVar <= 0) && !addVar[3].isTriggered) {
                addVar[3].initialVar = std::sqrt(std::sqrt(66.8));
                addVar[3].isTriggered = 1;
            }
            if (addVar[3].initialVar >= 0 && addIndex != 0) {
                double angleDegree = addVar[3].backwardVal(0);
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
                addVar[3].changeVar(0, 66.8, 100, speed);
            }
            //---------------------------------

            //animation 4.2
            if (addVar[4].initialVar >= 0) {
                for (int i = addIndex; i < arrSize; i++) {
                    std::string str = std::to_string(arr[i]);
                    sf::Vector2f newPos(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + addVar[4].forwardVal(0, 250), 250);
                    graphicalNode[i].set(str, FiraSansRegular, newPos.x, newPos.y, sf::Color::Black, sf::Color::White, anm::lightBlue);
                }
                for (int i = addIndex; i < arrSize - 1; i++) {
                    sf::Vector2f newPos(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130 + addVar[4].forwardVal(0, 250), 285);
                    arrowSprite[i].setPosition(newPos);
                }
                if (addIndex == 0) {
                    sf::Vector2f newHeadPos(anm::maxWidth/2 - (arrSize/2)*250 + 28 + addVar[4].forwardVal(0, 250), 80);
                    sf::Vector2f newArrowPos(anm::maxWidth/2 - (arrSize/2)*250 + 85 + addVar[4].forwardVal(0, 250), 145);
                    pHead.set("head", FiraSansRegular, newHeadPos.x, newHeadPos.y, sf::Color(22, 34, 41, 255), sf::Color(229, 184, 168, 255), sf::Color(168, 213, 229, 255));
                    pointerArrow.setPosition(newArrowPos);
                }
                addVar[4].changeVar(0, 250, 100, speed);
            }
            //-------------------------------------------------------

            //animation 4.3
            if (addVar[5].initialVar >= 0) {
                sf::Vector2f newPos(
                    anm::maxWidth/2 - (arrSize/2)*250 + addIndex*250, 
                    addVar[5].backwardVal(250)
                );
                newNode.set(str, FiraSansRegular, newPos.x, newPos.y , sf::Color::Black, sf::Color::White, anm::lightBlue);
                addVar[5].changeVar(250, 500, 100, speed);
            }
            //-----------------------------------------------------
            
            //animation 4.4
            if (addVar[6].initialVar >= 0) {
                newArrowSprite.setRotation(-addVar[6].backwardVal(0));
                addVar[6].changeVar(0, 90, 110, speed);
            }

            if (addVar[7].initialVar >= 0 || addVar[8].initialVar >= 0) {
                newArrowSprite.setPosition(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex)*250 + 35 + addVar[7].forwardVal(0, 95), addVar[8].backwardVal(285));
                newArrowSprite.setScale(defaultArrowScale);
                addVar[7].changeVar(0, 95, 170, speed);
                addVar[8].changeVar(0, 250, 110, speed);
            }
            else if (addIndex == 0) addAnimationOrder = 5;
            else addAnimationOrder = 7;
            //----------------------------------------------
            break;
        }
        case 5: {
            double angleDegree = addVar[9].forwardVal(0, 69.19320899);
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
            if (addVar[9].initialVar >= 0) addVar[9].changeVar(0, 69.19320899, 100, speed);
            else addAnimationOrder = 6;
            break;
        }
        case 6: {
            sf::Vector2f newHeadPos(anm::maxWidth/2 - (arrSize/2)*250 + 28 + addVar[10].backwardVal(0), 80);
            sf::Vector2f newArrowPos(anm::maxWidth/2 - (arrSize/2)*250 + 85 + addVar[10].backwardVal(0), 145);
            pHead.set("head", FiraSansRegular, newHeadPos.x, newHeadPos.y, sf::Color(22, 34, 41, 255), sf::Color(229, 184, 168, 255), sf::Color(168, 213, 229, 255));
            pointerArrow.setPosition(newArrowPos);
            if (addVar[10].initialVar) addVar[10].changeVar(0, 250, 100, speed);
            
            double angleDegree = addVar[11].backwardVal(0);
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
            if (addVar[11].initialVar >= 0) addVar[11].changeVar(0, 69.19320899, 100, speed);
            if (addVar[11].initialVar < 0 && addVar[10].initialVar < 0) addAnimationOrder = 7;
            break;
        }
        case 7: {
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
                for (int i = 0; i < arrSize; i++) {
                    std::string str = std::to_string(arr[i]);
                    graphicalNode[i].set(str, FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + i*250 + addVar[12].backwardVal(0), 250, sf::Color::Black, sf::Color::White, anm::lightBlue);
                }
                for (int i = 0; i < arrSize - 1; i++) {
                    arrowSprite[i].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130 + addVar[12].backwardVal(0), 285);
                }
                sf::Vector2f newHeadPos(anm::maxWidth/2 - (arrSize/2)*250 + 28 + addVar[12].backwardVal(0), 80);
                sf::Vector2f newArrowPos(anm::maxWidth/2 - (arrSize/2)*250 + 85 + addVar[12].backwardVal(0), 145);
                pHead.set("head", FiraSansRegular, newHeadPos.x, newHeadPos.y, sf::Color(22, 34, 41, 255), sf::Color(229, 184, 168, 255), sf::Color(168, 213, 229, 255));
                pointerArrow.setPosition(newArrowPos);
                addVar[12].changeVar(0, 250, 140, speed);
            }
            else {
                isAdd = 0;
                isInit = 1;
                addAnimationOrder = 1;
            }
            break;
        }
        case 8: {
            addVar[13].isTriggered = 1;
            double angleDegree = 66.8;
            sf::Vector2f newScale(
                addVar[13].forwardVal(0, 110/std::cos(66.8*std::atan(1)*4/180)) / arrowSprite[addIndex - 1].getLocalBounds().width, 
                50 / arrowSprite[addIndex - 1].getLocalBounds().height
            );
            sf::Vector2f newPos(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex-1)*250 + 150, 295);
            arrowSprite[addIndex - 1].setRotation(66.8);
            arrowSprite[addIndex - 1].setScale(newScale);
            arrowSprite[addIndex - 1].setPosition(newPos);
            if (addVar[13].initialVar >= 0) addVar[13].changeVar(0, 110/std::cos(66.8*std::atan(1)*4/180), 150, speed);
            else {
                addAnimationOrder = 4;
                addVar[3].initialVar = -1;
            }
            break;
        }
        }
    }
    for (int i = 0; i < arrSize; i++) {
        window.draw(graphicalNode[i].box);
        window.draw(graphicalNode[i].number);
    }
    for (int i = 0; i < arrSize - 1; i++) {
        window.draw(arrowSprite[i]);
    }
    if (addIndex == arrSize && ((addAnimationOrder > 3 && addAnimationOrder < 7) || addAnimationOrder == 8) && addVar[13].isTriggered) window.draw(arrowSprite[addIndex - 1]);
    if (!addVar[8].isTriggered) {
        window.draw(newNode.box);
        window.draw(newNode.number);
    }
    if (addIndex != arrSize && addVar[2].isTriggered && addAnimationOrder < 7) window.draw(newArrowSprite);
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
    int addIndex = 0;
    int addAnimationOrder = 1;
    //---------------------------

    //Font
    if (!ComfortaaRegular.loadFromFile("fonts/Comfortaa-Regular.ttf")) {
        std::cout << "Error when loading font Comfortaa-Regular\n";
    }
    if (!FiraSansRegular.loadFromFile("fonts/FiraSans-Regular.ttf")) {
        std::cout << "Error when loading font FiraSans-Regular\n";
    }
    //---------------------

    //Buttons
    sf::Text createButton;
    anm::setText(createButton, ComfortaaRegular, "Create", 100, 10, anm::maxHeight/2 + 200, anm::whiteBlue);
    sf::Text addButton;
    anm::setText(addButton, ComfortaaRegular, "Add", 100, 10, anm::maxHeight/2 + 400, anm::whiteBlue);
    ImageButton playButton("img/playButton.png", "img/playButtonHoverred.png", 100, 100, sf::Vector2f(anm::maxWidth/2 - 50, anm::maxHeight - 400));
    ImageButton pauseButton("img/pauseButton.png", "img/pauseButtonHoverred.png", 100, 100, sf::Vector2f(anm::maxWidth/2 - 50, anm::maxHeight - 400));
    ImageButton nextButton("img/nextButton.png", "img/nextButtonHoverred.png", 100, 100, sf::Vector2f(anm::maxWidth/2 + 100, anm::maxHeight - 400));
    ImageButton prevButton("img/previousButton.png", "img/previousButtonHoverred.png", 100, 100, sf::Vector2f(anm::maxWidth/2 - 200, anm::maxHeight - 400));
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
            //------------------------------------------
            if (playButton.isClicked(window) && isPause) isPause = 0;
            else if (pauseButton.isClicked(window) && !isPause) isPause = 1;
            if (event.type == sf::Event::Closed) 
                window.close();
        }
        window.clear();  
        if (!isPause) pauseButton.activate(window);
        else playButton.activate(window);
        nextButton.activate(window);
        prevButton.activate(window);
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

        if (isAdd) addAnimation(window, addAnimationOrder, arr, graphicalNode, pHead, pointerArrow, addVar, arrowSprite, arrSize, 0, -231, 1);
        window.display();
    }
}