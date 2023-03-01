#include "../header/Menu.h"

Menu::Menu() {

    // Create window

    sf::RenderWindow window;
    const int maxWidth = sf::VideoMode::getDesktopMode().width;
    const int maxHeight = sf::VideoMode::getDesktopMode().height;
    window.create(sf::VideoMode(maxWidth - 100, maxHeight - 100), "Data Visual", sf::Style::Default);
    window.setPosition(sf::Vector2i(30, 30));
    window.setVerticalSyncEnabled(true);

    //----------------------------------------

    // Set Font
    sf::Font TiltWarp;
    if (!TiltWarp.loadFromFile("fonts/TiltWarp-Regular.ttf")) {
        std::cout << "Error when loading font TiltWarp\n";
    }
    sf::Font GreatVibes;
    if (!GreatVibes.loadFromFile("fonts/GreatVibes-Regular.ttf")) {
        std::cout << "Error when loading font GreatVibes\n";
    }
    sf::Font ComfortaaRegular;
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


    //Title appearance

    for (int i = 0; i < 255; i++) {
        window.clear();
        title.setFillColor(sf::Color(145, 174, 226, i));
        option1.setFillColor(sf::Color(231, 237, 251, i));
        option2.setFillColor(sf::Color(231, 237, 251, i));
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
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                std::cout << localPosition.x << ' ' << localPosition.y << std::endl;
                std::cout << "Pressed\n";
            }
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