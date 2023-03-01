#include "../header/Menu.h"

Menu::Menu() {

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
    anm::setText(title, GreatVibes, "Data Visual", 350, maxWidth/2 - 790, maxHeight/2 - 600, 145, 174, 226, 0);
    sf::Text option1, option2;
    anm::setText(option1, ComfortaaRegular, "start", 200, maxWidth/2 - 250, maxHeight/2 - 50, 231, 237, 251, 255);
    anm::setText(option2, ComfortaaRegular, "end", 200, maxWidth/2 - 200, maxHeight/2 + 200, 231, 237, 251, 255);
    // -----------------------------------


    //Loading image

    sf::Texture texture;
    if (!texture.loadFromFile("img/menu_background2.jpg"));
    sf::Sprite sprite(texture);
    sf::Vector2f scaleFactor(window.getSize().x / sprite.getLocalBounds().width, window.getSize().y / sprite.getLocalBounds().height);
    sprite.setScale(scaleFactor);

    // --------------------------------------------------------


    //Text appearance

    for (int i = 0; i < 255; i++) {
        title.setFillColor(sf::Color(145, 174, 226, i));
        option1.setFillColor(sf::Color(231, 237, 251, i));
        option2.setFillColor(sf::Color(231, 237, 251, i));
        window.clear();
        window.draw(sprite);
        window.draw(title);
        window.draw(option1);
        window.draw(option2);
        window.display();
    }

    //---------------------------------

    sf::Vector2i localPosition;

    while (window.isOpen()) { // main loop
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            
            localPosition = sf::Mouse::getPosition(window);

            // Hover 

            if (anm::isHover(localPosition, 1192, 901, 1697, 1047)) {
                option1.setFillColor(sf::Color(145, 174, 226, 255));
            } else {
                option1.setFillColor(sf::Color(231, 237, 251, 255));
            }
            if (anm::isHover(localPosition, 1239, 1143, 1636, 1305)) {
                option2.setFillColor(sf::Color(145, 174, 226, 255));
            } else {
                option2.setFillColor(sf::Color(231, 237, 251, 255));
            }

            //------------------------------------------------------------------
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && anm::isHover(localPosition, 1192, 901, 1697, 1047)) 
                nextPage();
        }

        // Draw

        window.clear();
        window.draw(sprite);
        window.draw(title);
        window.draw(option1);
        window.draw(option2);
        window.display();

        //-------------------
    }
}

void Menu::nextPage() {

     //Loading image

    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("img/menu_background2.jpg"));
    sf::Sprite menuBackgroundSprite(menuBackgroundTexture);
    sf::Vector2f scaleFactor(window.getSize().x / menuBackgroundSprite.getLocalBounds().width, window.getSize().y / menuBackgroundSprite.getLocalBounds().height);
    menuBackgroundSprite.setScale(scaleFactor);

    // --------------------------------------------------------

    // Set text
    sf::Text staticArray, dynamicArray, linkedList, stack, queue;
    anm::setText(staticArray, ComfortaaRegular, "Static Array", 150, maxWidth/2 - 500, maxHeight/2 - 800, 231, 237, 251, 255);
    anm::setText(dynamicArray, ComfortaaRegular, "Dynamic Array", 150, maxWidth/2 - 600, maxHeight/2 - 500, 231, 237, 251, 255);
    anm::setText(linkedList, ComfortaaRegular, "Linked List", 150, maxWidth/2 - 450, maxHeight/2 - 200, 231, 237, 251, 255);
    anm::setText(stack, ComfortaaRegular, "Stack", 150, maxWidth/2 - 240, maxHeight/2 + 100, 231, 237, 251, 255);
    anm::setText(queue, ComfortaaRegular, "Queue", 150, maxWidth/2 - 290, maxHeight/2 + 400, 231, 237, 251, 255);
    //-----------------------------------------------------------

    sf::Event event;
    sf::Vector2i localPosition;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            localPosition = sf::Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))   
                std::cout << localPosition.x << ' ' << localPosition.y << std::endl;

            //Hover
            
            if (anm::isHover(localPosition, 942, 118, 1866, 288)) {
                staticArray.setFillColor(sf::Color(145, 174, 226, 255));
            } else {
                staticArray.setFillColor(sf::Color(231, 237, 251, 255));
            }
            if (anm::isHover(localPosition, 846, 416, 1987, 587)) {
                dynamicArray.setFillColor(sf::Color(145, 174, 226, 255));
            } else {
                dynamicArray.setFillColor(sf::Color(231, 237, 251, 255));
            }
            if (anm::isHover(localPosition, 980, 714, 1865, 857)) {
                linkedList.setFillColor(sf::Color(145, 174, 226, 255));
            } else {
                linkedList.setFillColor(sf::Color(231, 237, 251, 255));
            }
            if (anm::isHover(localPosition, 1196, 1016, 1647, 1154)) {
                stack.setFillColor(sf::Color(145, 174, 226, 255));
            } else {
                stack.setFillColor(sf::Color(231, 237, 251, 255));
            }
             if (anm::isHover(localPosition, 1140, 1317, 1694, 1446)) {
                queue.setFillColor(sf::Color(145, 174, 226, 255));
            } else {
                queue.setFillColor(sf::Color(231, 237, 251, 255));
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