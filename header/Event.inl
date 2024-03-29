template <typename Data>
bool evn::isHovered(sf::RenderWindow &window, Data &data) {
    sf::Vector2i localPosition(sf::Mouse::getPosition(window));
    sf::Vector2f localPositionF(static_cast<float>(localPosition.x), static_cast<float>(localPosition.y));
    localPositionF = window.mapPixelToCoords(localPosition);
    sf::FloatRect dataBounds = data.getGlobalBounds();
    sf::Vector2f startPoint(dataBounds.left, dataBounds.top);
    sf::Vector2f endPoint(dataBounds.left + dataBounds.width, dataBounds.top + dataBounds.height);
    return (
        localPositionF.x >= dataBounds.left && 
        localPositionF.x <= dataBounds.left + dataBounds.width && 
        localPositionF.y >= dataBounds.top && 
        localPositionF.y <= dataBounds.top + dataBounds.height
    );
}

template <typename Data>
bool evn::isLeftClicked(sf::RenderWindow &window, sf::Event &event, Data &data) {
    return (evn::isHovered(window, data) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.type == sf::Event::MouseButtonPressed);
}

template <typename Data>    
bool evn::isRightClicked(sf::RenderWindow &window,sf::Event &event, Data &data) {
    return (evn::isHovered(window, data) && sf::Mouse::isButtonPressed(sf::Mouse::Right) && event.type == sf::Event::MouseButtonPressed);
}

