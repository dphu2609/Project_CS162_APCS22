#include "../header/Menu.h"

Menu::Menu() {
    sf::Texture texture;
    if (!texture.loadFromFile("img/menu_background.png"));
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::RenderWindow window;
    window.create(sf::VideoMode(1900, 1200), "Algo Visual", sf::Style::Default);
    while (window.isOpen()) {
        sf::Event event;
        window.clear();
        window.draw(sprite);
        window.display();
        while (window.pollEvent(event)) {
            localPosition = sf::Mouse::getPosition(window);
            // std::cout << localPosition.x << ' ' << localPosition.y << std::endl;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) std::cout << "Pressed\n";
            if (event.type == sf::Event::Closed) 
                window.close();
        }
    }
}