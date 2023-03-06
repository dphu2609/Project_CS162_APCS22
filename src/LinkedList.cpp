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

void LinkedList::addAnimation(sf::RenderWindow &window, std::vector<int> &arr, std::vector<GraphicalNode> &graphicalNode, std::vector<AnimationVar> &addVar,  std::vector<sf::Sprite> &arrowSprite, ,int arrSize, int addIndex, double speed) {
    GraphicalNode newNode;
    if (addVar[1].initialVar >= 0) { //animation 1
        addVar[1].initialVar -= 0.025*speed;
    }
    else if (addVar[2].initialVar >= 0) { //animation 2
        newArrowSprite.setRotation(-90);
        newArrowSprite.setPosition(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex)*250 + 35, 500);
        newArrowSprite.setScale((-std::pow(initialArrowLength, 2) + 120) / newArrowSprite.getLocalBounds().width, 50 / newArrowSprite.getLocalBounds().height);
        addVar[2].initialVar -= (std::sqrt(120)/80)*speed;
        window.draw(newArrowSprite);
    }
    else if (addVar[3].initialVar >= 0 && !addVar[3].isTriggered) { //animation 3
        double initialLength = 110;
        double initialAngle = -std::pow(initialAngleVar, 4) + 66.8;
        arrowSprite[addIndex - 1].setRotation(initialAngle);
        float temp = initialAngle*(std::atan(1)*4)/180;
        arrowSprite[addIndex - 1].setScale(sf::Vector2f((initialLength/std::cos(temp)) / newArrowSprite.getLocalBounds().width, 50 / newArrowSprite.getLocalBounds().height));
        arrowSprite[addIndex - 1].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex-1)*250 + 130 + initialAngle*0.32934131737, 285 + initialAngle*0.19461077844);
        initialAngleVar -= (std::sqrt(std::sqrt(66.8))/100)*speed;
        std::cout << "1/n";
    }
    else if (!addVar[4].isTriggered) {
        if (addVar[3].initialVar <= 0 && !addVar[3].isTriggered) {
            addVar[3].initialVar = std::sqrt(std::sqrt(66.8));
            addVar[3].isTriggered = 1;
        }
        if (addVar[3].initialVar >= 0) {
            double initialLength = 110;
            double initialAngle = std::pow(initialAngleVar, 4);
            arrowSprite[addIndex - 1].setRotation(initialAngle);
            float temp = initialAngle*(std::atan(1)*4)/180;
            arrowSprite[addIndex - 1].setScale(sf::Vector2f((initialLength/std::cos(temp)) / newArrowSprite.getLocalBounds().width, 50 / newArrowSprite.getLocalBounds().height));
            arrowSprite[addIndex - 1].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex-1)*250 + 130 + initialAngle*0.32934131737, 285 + initialAngle*0.19461077844);
            add -= (std::sqrt(std::sqrt(66.8))/100)*speed;
        }
        if (transitionVar >= 0) {
            for (int i = addIndex; i < arrSize; i++) {
                std::string str = std::to_string(arr[i]);
                graphicalNode[i].set(str, FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + i*250 - std::pow(transitionVar, 2) + 250, 250, sf::Color::Black, sf::Color::White, anm::lightBlue);
            }
            for (int i = addIndex; i < arrSize - 1; i++) {
                arrowSprite[i].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + i*250 + 130 - std::pow(transitionVar, 2) + 250, 285);
            }
            transitionVar -= (std::sqrt(250)/100)*speed;
            isInit = 0;
        }
        else {
            isInit = 1;
            isInserted = 1;
        }
        for (int i = 0; i < arrSize; i++) {
            window.draw(graphicalNode[i].box);
            window.draw(graphicalNode[i].number);
        }
        for (int i = 0; i < arrSize - 1; i++) {
            window.draw(arrowSprite[i]);
        }
    }
    newNode.set("12", FiraSansRegular, anm::maxWidth/2 - (arrSize/2)*250 + (addIndex)*250, std::pow(iniitialNewNodePos, 4) + 500, sf::Color::Black, sf::Color::White, anm::lightBlue);
    window.draw(newNode.box);
    window.draw(newNode.number);
    if (initialArrowLength < 0) window.draw(newArrowSprite);
}


void LinkedList::init(sf::RenderWindow &window) {
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
    for (int i = 0; i < 7; i++) {
        arrowSprite[i].setTexture(arrowTexture);
    }
    //------------------------------

    std::vector arr = {-1, 10, 20000, -5, 78, 1310, -99};
    int arrSize = arr.size();
    // LinkedList<int> list;
    // list.create(arr, 1);
    std::vector<GraphicalNode> graphicalNode(15);

    //Init variable for effect
    int nodeSize = 0;
    int arrowSize = 0;
    int delayTime = 10;
    int timeIndex = 0;
    bool isAdd = 0;
    bool isOdd = 0;
    //---------------------------

    //Add variable
    std::vector<AnimationVar> addVar(5);
    int addIndex = 2;
    bool isInserted = 0;

    //1st animation
    double iniitialNewNodePos;
    //------------------------

    //2st animation
    double initialArrowLength = 0;
    //--------------------------

    //3rd animation
    double initialAngleVar = 0;
    bool isAnimation3Triggered = 0;
    //----------------------------

    //4th animation 
    double transitionVar = 0;
    //-----------------------
    GraphicalNode newNode;
    sf::Sprite newArrowSprite;
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
                addVar[1].initialVar = std::sqrt(std::sqrt(400));
                addVar[2].initialVar = std::sqrt(120);
                addVar[3].initialVar = std::sqrt(std::sqrt(66.8));
                addVar[4].initialVar = std::sqrt(250);
                for (int i = 1; i <= 4; i++) addVar[i].isTriggered = 0;
                // iniitialNewNodePos = std::sqrt(std::sqrt(400));
                // initialAngleVar = std::sqrt(std::sqrt(66.8));
                // arrowSprite[addIndex - 1].setPosition(anm::maxWidth/2 - (arrSize/2)*250 + (addIndex - 1)*250 + 130, 285);
                // arrowSprite[addIndex - 1].setRotation(0);
                // arrowSprite[addIndex - 1].setScale(sf::Vector2f(110 / arrowSprite[0].getLocalBounds().width, 50 / arrowSprite[0].getLocalBounds().height));
                // initialArrowLength = std::sqrt(120);
                // transitionVar = std::sqrt(250);
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

        if (isInit) {
            for (int i = 0; i < nodeSize; i++) {
                window.draw(graphicalNode[i].box);
                window.draw(graphicalNode[i].number);
            }
            for (int i = 0; i < arrowSize; i++) {
                window.draw(arrowSprite[i]);
            }
        }

        if (isAdd) addAnimation(window, arr, graphicalNode, arrowSprite, iniitialNewNodePos, arrSize, initialArrowLength, newArrowSprite, initialAngleVar, addIndex, 1, isInserted, isInit, transitionVar, isAnimation3Triggered);
        window.display();

        //Init handle
        initHandle(isInit, isOdd, timeIndex, delayTime, nodeSize, arrowSize, arrSize);
        //---------------------------------------------------
    }
}