#include "Coin.h"
Coin::Coin(float x, float y) {
    speed = 7.0f;
    shape.setRadius(16.f);
    shape.setFillColor(sf::Color(255, 215, 0));
    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(sf::Color(180, 130, 0));
    shape.setOrigin(16.f, 16.f);
    shape.setPosition(x, y);
}
void Coin::update() { shape.move(0, speed); }
void Coin::draw(sf::RenderWindow& w) {
    // Base coin
    w.draw(shape);

    // Simple highlight to make it look shiny
    sf::CircleShape shine(shape.getRadius() * 0.4f);
    shine.setFillColor(sf::Color(255, 255, 255, 140));
    shine.setOrigin(shine.getRadius(), shine.getRadius());
    sf::Vector2f pos = shape.getPosition();
    shine.setPosition(pos.x - shape.getRadius() * 0.3f, pos.y - shape.getRadius() * 0.5f);
    w.draw(shine);
}
sf::FloatRect Coin::getBounds() const { return shape.getGlobalBounds(); }