#pragma once

#include <SFML/Graphics.hpp>

namespace evn {
    template <typename Data>
    bool isHovered(sf::RenderWindow &window, Data &data);

    template <typename Data>
    bool isLeftClicked(sf::RenderWindow &window, sf::Event &event, Data &data);

    template <typename Data>
    bool isRightClicked(sf::RenderWindow &window, sf::Event &event ,Data &data);
};

#include "Event.inl"