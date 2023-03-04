#include "../header/Program.h"

#include <bits/stdc++.h>


Program::Program() {

    // Create window
    window.create(sf::VideoMode(maxWidth - 100, maxHeight - 100), "Data Visual", sf::Style::Default);
    window.setPosition(sf::Vector2i(30, 30));
    window.setVerticalSyncEnabled(true);
    //----------------------------------------

    // Set Font
    if (!TiltWarp.loadFromFile("fonts/TiltWarp-Regular.ttf")) {
        std::cout << "Error when loading font TiltWarp\n";
    }
    if (!GreatVibes.loadFromFile("fonts/GreatVibes-Regular.ttf")) {
        std::cout << "Error when loading font GreatVibes\n";
    }
    if (!ComfortaaRegular.loadFromFile("fonts/Comfortaa-Regular.ttf")) {
        std::cout << "Error when loading font Comfortaa-Regular\n";
    }
    //----------------------------------------------

    // Set color 
    sf::Color lightBlue = anm::lightBlue;
    sf::Color whiteBlue = anm::whiteBlue;
    //------------------------------------------------

    // Set text
    sf::Text title;
    anm::setText(title, GreatVibes, "Data Visual", 350, maxWidth/2 - 790, maxHeight/2 - 600, lightBlue);
    sf::Text option1, option2;
    anm::setText(option1, ComfortaaRegular, "start", 200, maxWidth/2 - 250, maxHeight/2 - 50, whiteBlue);
    anm::setText(option2, ComfortaaRegular, "end", 200, maxWidth/2 - 200, maxHeight/2 + 200, whiteBlue);
    // -----------------------------------


    //Loading image
    sf::Texture texture;
    if (!texture.loadFromFile("img/menu_background2.jpg"));
    sf::Sprite sprite(texture);
    sf::Vector2f scaleFactor(window.getSize().x / sprite.getLocalBounds().width, window.getSize().y / sprite.getLocalBounds().height);
    sprite.setScale(scaleFactor);
    // --------------------------------------------------------


    //Text appearance
    int i = 0;
    while(window.isOpen() && i < 255) {
        sf::Event event;
        localPosition = sf::Mouse::getPosition(window);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
        }
        title.setFillColor(sf::Color(145, 174, 226, i));
        anm::hoverText(option1, localPosition, sf::Color(145, 174, 226, i), sf::Color(231, 237, 251, i));
        anm::hoverText(option2, localPosition, sf::Color(145, 174, 226, i), sf::Color(231, 237, 251, i));
        window.clear();
        window.draw(sprite);
        window.draw(title);
        window.draw(option1);
        window.draw(option2);
        window.display();
        i++;
    }
    //---------------------------------

    // sf::Font font;
    // GraphicalNode node;
    // node.set("100", font, 10, 10, sf::Color::Black, sf::Color::White, anm::lightBlue);

    
    while (window.isOpen()) { // main loop
        sf::Event event;
        window.clear();
        window.draw(sprite);
        window.draw(title);
        window.draw(option1);
        window.draw(option2);
        // window.draw(node.box);
        // window.draw(node.number);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            
            localPosition = sf::Mouse::getPosition(window);

            // Hover 
            anm::hoverText(option1, localPosition, lightBlue, whiteBlue);
            anm::hoverText(option2, localPosition, lightBlue, whiteBlue);
            //------------------------------------------------------------------
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && anm::isHover(option1, localPosition)) 
                nextPage();
        }

        // Draw
        window.display();
        //-------------------
    }
}

void Program::nextPage() {

     //Loading image
    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("img/menu_background2.jpg"));
    sf::Sprite menuBackgroundSprite(menuBackgroundTexture);
    sf::Vector2f scaleFactor(window.getSize().x / menuBackgroundSprite.getLocalBounds().width, window.getSize().y / menuBackgroundSprite.getLocalBounds().height);
    menuBackgroundSprite.setScale(scaleFactor);
    // --------------------------------------------------------

    
    // Set color 
    sf::Color lightBlue = anm::lightBlue;
    sf::Color whiteBlue = anm::whiteBlue;
    //------------------------------------------------

    // Set text
    sf::Text staticArray, dynamicArray, linkedList, stack, queue;
    anm::setText(staticArray, ComfortaaRegular, "Static Array", 150, maxWidth/2 - 500, maxHeight/2 - 800, whiteBlue);
    anm::setText(dynamicArray, ComfortaaRegular, "Dynamic Array", 150, maxWidth/2 - 600, maxHeight/2 - 500, whiteBlue);
    anm::setText(linkedList, ComfortaaRegular, "Linked List", 150, maxWidth/2 - 450, maxHeight/2 - 200, whiteBlue);
    anm::setText(stack, ComfortaaRegular, "Stack", 150, maxWidth/2 - 240, maxHeight/2 + 100, whiteBlue);
    anm::setText(queue, ComfortaaRegular, "Queue", 150, maxWidth/2 - 290, maxHeight/2 + 400, whiteBlue);
    //-----------------------------------------------------------

    sf::Event event;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            localPosition = sf::Mouse::getPosition(window);

            //Hover
            
            anm::hoverText(staticArray, localPosition, lightBlue, whiteBlue);
            anm::hoverText(dynamicArray, localPosition, lightBlue, whiteBlue);
            anm::hoverText(linkedList, localPosition, lightBlue, whiteBlue);
            anm::hoverText(stack, localPosition, lightBlue, whiteBlue); 
            anm::hoverText(queue, localPosition, lightBlue, whiteBlue);

            if (anm::isHover(linkedList, localPosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) linkedListPage();

            //------------------------------------------------------
            if (event.type == sf::Event::Closed) 
                window.close();
        }
        window.clear();
        window.draw(menuBackgroundSprite);
        window.draw(staticArray);
        window.draw(dynamicArray);
        window.draw(linkedList);
        window.draw(stack);
        window.draw(queue);
        window.display();
    }
}

double funcX(double &x, double timeDelay) {
    x -= timeDelay;
    return x*x*x*x + 500;
}

double funcY(double &x, bool &way, double timeDelay) {
    if (way) {
        return std::sqrt(100*100 - (x-200)*(x-200)) + 200;
    } else {
        return -std::sqrt(100*100 - (x-200)*(x-200)) + 200;
        // return -x*x;
    }
}

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

void Program::linkedListPage() {
    //Page setup
    sf::Text createButton;
    anm::setText(createButton, ComfortaaRegular, "Create", 100, 10, maxHeight - 800, anm::whiteBlue);
    sf::Text addButton;
    anm::setText(addButton, ComfortaaRegular, "Add", 100, 10, maxHeight - 400, anm::whiteBlue);
    sf::Font FiraSansRegular;
    if (!FiraSansRegular.loadFromFile("fonts/FiraSans-Regular.ttf")) {
        std::cout << "Error when loading font FiraSans-Regular\n";
    }
    //------------------------

    //----------------------
    sf::Texture arrowTexture;
    if (!arrowTexture.loadFromFile("img/rightArrow.png"));
    sf::Sprite arrowSprite[6];
    for (int i = 0; i < 6; i++) {
        arrowSprite[i].setTexture(arrowTexture);
        sf::Vector2f scaleFactor(110 / arrowSprite[i].getLocalBounds().width, 50 / arrowSprite[i].getLocalBounds().height);
        arrowSprite[i].setScale(scaleFactor);
    }
    //------------------------------

    int arr[6] = {-1, 10, 20000, -5, 78, 1310};
    int n = 6;
    LinkedList<int> list;
    list.create(arr, 1);
    std::vector<GraphicalNode> graphicalNode(10);

    //Init variable for effect
    int nodeSize = 0;
    int arrowSize = 0;
    int delayTime = 10;
    int timeIndex = 0;
    bool isInit = 0;
    bool isAdd = 0;
    bool isOdd = 0;
    //---------------------------

    //Add variable
    int addIndex = 4;
    double pos;
    GraphicalNode newNode;
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
                for (int i = 0; i < n; i++) {
                    std::string str = std::to_string(arr[i]);
                    graphicalNode[i].set(str, FiraSansRegular, anm::maxWidth/2 - (n/2)*250 + i*250, 250, sf::Color::Black, sf::Color::White, anm::lightBlue);
                    arrowSprite[i].setPosition(anm::maxWidth/2 - (n/2)*250 + i*250 + 130, 285);
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
                pos = std::sqrt(std::sqrt(800));
            }
            //-------------------------------------------

            if (event.type == sf::Event::Closed) 
                window.close();
        }
        window.clear();  
        window.draw(createButton);
        window.draw(addButton);
        // graphicalNode[0].set(str, FiraSansRegular, funcX(x, way, 0.4), funcY(x, way, 0.4), sf::Color::Black, sf::Color::White, anm::lightBlue);
        // window.draw(graphicalNode[0].box);
        // window.draw(graphicalNode[0].number);

        if (isInit) {
            for (int i = 0; i < nodeSize; i++) {
                window.draw(graphicalNode[i].box);
                window.draw(graphicalNode[i].number);
            }
            for (int i = 0; i < arrowSize; i++) {
                window.draw(arrowSprite[i]);
            }
        }

        if (isAdd) {
            if (pos >= 0) newNode.set("12", FiraSansRegular, anm::maxWidth/2 - (n/2)*250 + (addIndex - 1)*250, funcX(pos, 0.015), sf::Color::Black, sf::Color::White, anm::lightBlue);
            window.draw(newNode.box);
            window.draw(newNode.number);
        }
        window.display();

        //Init handle
        initHandle(isInit, isOdd, timeIndex, delayTime, nodeSize, arrowSize, n);
        //---------------------------------------------------
    }
}