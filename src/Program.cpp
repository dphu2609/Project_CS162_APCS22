#include <Program.h>

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

    // Set text
    sf::Text title;
    anm::setText(title, GreatVibes, "Data Visual", 350, maxWidth/2 - 790, maxHeight/2 - 600, anm::lightBlue);
    sf::Text option1, option2;
    anm::setText(option1, ComfortaaRegular, "start", 200, maxWidth/2 - 250, maxHeight/2 - 50, anm::whiteBlue);
    anm::setText(option2, ComfortaaRegular, "end", 200, maxWidth/2 - 200, maxHeight/2 + 200, anm::whiteBlue);
    sf::Text staticArray, dynamicArray, linkedList, stack, queue;
    anm::setText(staticArray, ComfortaaRegular, "Static Array", 150, maxWidth/2 - 500, maxHeight/2 - 800, anm::whiteBlue);
    anm::setText(dynamicArray, ComfortaaRegular, "Dynamic Array", 150, maxWidth/2 - 600, maxHeight/2 - 500, anm::whiteBlue);
    anm::setText(linkedList, ComfortaaRegular, "Linked List", 150, maxWidth/2 - 450, maxHeight/2 - 200, anm::whiteBlue);
    anm::setText(stack, ComfortaaRegular, "Stack", 150, maxWidth/2 - 240, maxHeight/2 + 100, anm::whiteBlue);
    anm::setText(queue, ComfortaaRegular, "Queue", 150, maxWidth/2 - 290, maxHeight/2 + 400, anm::whiteBlue);
    // -----------------------------------


    //Loading image
    sf::Texture texture;
    if (!texture.loadFromFile("img/menu_background2.jpg"));
    sf::Sprite sprite(texture);
    sf::Vector2f scaleFactor(window.getSize().x / sprite.getLocalBounds().width, window.getSize().y / sprite.getLocalBounds().height);
    sprite.setScale(scaleFactor);
    // --------------------------------------------------------


    //Text appearance
    int i = 100;
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

    bool isNextPage = 0;
    
    while (window.isOpen()) { // main loop
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            
            localPosition = sf::Mouse::getPosition(window);

            // Hover 
            if (!isNextPage) {
                anm::hoverText(option1, localPosition, anm::lightBlue, anm::whiteBlue);
                anm::hoverText(option2, localPosition, anm::lightBlue, anm::whiteBlue);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && anm::isHover(option1, localPosition)) isNextPage = 1;
            }
            else {
                anm::hoverText(staticArray, localPosition, anm::lightBlue, anm::whiteBlue);
                anm::hoverText(dynamicArray, localPosition, anm::lightBlue, anm::whiteBlue);
                anm::hoverText(linkedList, localPosition, anm::lightBlue, anm::whiteBlue);
                anm::hoverText(stack, localPosition, anm::lightBlue, anm::whiteBlue); 
                anm::hoverText(queue, localPosition, anm::lightBlue, anm::whiteBlue);

                if (anm::isHover(linkedList, localPosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    LinkedList linkedListPage(window);
                }
            }
            //------------------------------------------------------------------
        }

        // Draw
        window.clear();
        window.draw(sprite);
        if (!isNextPage) {
            window.draw(title);
            window.draw(option1);
            window.draw(option2);
        }
        else {
            window.draw(staticArray);
            window.draw(dynamicArray);
            window.draw(linkedList);
            window.draw(stack);
            window.draw(queue);
        }
        window.display();
        //-------------------
    }
}
