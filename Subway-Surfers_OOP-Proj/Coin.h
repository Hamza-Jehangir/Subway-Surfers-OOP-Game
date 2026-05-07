#pragma once
#include <SFML/Graphics.hpp>
class Coin {
private: sf::CircleShape shape; float speed;
public: Coin(float x, float y); void update(); void draw(sf::RenderWindow& w); sf::FloatRect getBounds() const;
};