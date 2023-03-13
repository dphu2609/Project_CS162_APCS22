#pragma once

#include <SFML/Graphics.hpp>

namespace evn {
    template <typename Data>
    bool isHoverred(sf::RenderWindow &window, Data &data);

    template <typename Data>
    bool isLeftClicked(sf::RenderWindow &window, Data &data);

    template <typename Data>
    bool isRightClicked(sf::RenderWindow &window, Data &data);
};

#include "Event.inl"