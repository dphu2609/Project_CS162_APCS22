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

            if (anm::isHover(linkedList, localPosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                LinkedList linkedListPage;
                linkedListPage.init(window);
            }

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
