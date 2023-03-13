template <typename Data>
bool evn::isHoverred(sf::RenderWindow &window, Data &data) {
    sf::Vector2i localPosition(sf::Mouse::getPosition(window));
    sf::FloatRect dataBounds = data.getGlobalBounds();
    sf::Vector2f startPoint(dataBounds.left, dataBounds.top);
    sf::Vector2f endPoint(dataBounds.left + dataBounds.width, dataBounds.top + dataBounds.height);
    return (
        localPosition.x >= dataBounds.left && 
        localPosition.x <= dataBounds.left + dataBounds.width && 
        localPosition.y >= dataBounds.top && 
        localPosition.y <= dataBounds.top + dataBounds.height
    );
}

template <typename Data>
bool evn::isLeftClicked(sf::RenderWindow &window, Data &data) {
    return (evn::isHoverred(window, data) && sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

template <typename Data>
bool evn::isRightClicked(sf::RenderWindow &window, Data &data) {
    return (evn::isHoverred(window, data) && sf::Mouse::isButtonPressed(sf::Mouse::Right));
}

