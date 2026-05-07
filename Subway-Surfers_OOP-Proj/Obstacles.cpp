#include "Obstacles.h"
#include <cstdlib>

Obstacle::Obstacle(float startX, float startY) {
    speed = 7.0f;
    shape.setPosition(startX, startY);

    // Shared visual styling for all obstacles
    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(sf::Color(0, 0, 0, 180));
}
void Obstacle::update() { shape.move(0, speed); }
void Obstacle::draw(sf::RenderWindow& window) { window.draw(shape); }
sf::FloatRect Obstacle::getBounds() const { return shape.getGlobalBounds(); }

Train::Train(float x, float y) : Obstacle(x, y) {
    // Randomized train length for variety
    float baseLength = 170.f;
    float extra = static_cast<float>(std::rand() % 120); // 0..119
    float length = baseLength + extra;

    shape.setSize(sf::Vector2f(80.f, length));
    shape.setFillColor(sf::Color(200, 50, 60)); // main body color
    shape.setOrigin(40.f, length * 0.5f);
}

void Train::draw(sf::RenderWindow& window) {
    // Draw main body
    window.draw(shape);

    // Compute useful values relative to the main rectangle
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();

    // Roof stripe
    sf::RectangleShape roof(sf::Vector2f(size.x * 0.9f, 10.f));
    roof.setFillColor(sf::Color(160, 40, 50));
    roof.setOrigin(roof.getSize().x * 0.5f, size.y * 0.5f + 5.f);
    roof.setPosition(pos);
    window.draw(roof);

    // Front light (bottom center)
    sf::CircleShape light(6.f);
    light.setFillColor(sf::Color(255, 240, 180));
    light.setOrigin(light.getRadius(), -size.y * 0.5f + 10.f);
    light.setPosition(pos);
    window.draw(light);

    // Windows along the body
    int windowCount = 3;
    float segment = size.y / (windowCount + 1);
    for (int i = 1; i <= windowCount; ++i) {
        sf::RectangleShape win(sf::Vector2f(28.f, 18.f));
        win.setFillColor(sf::Color(220, 235, 250));
        win.setOutlineThickness(1.5f);
        win.setOutlineColor(sf::Color(30, 40, 60));

        // Windows centered horizontally on the train, spaced vertically
        win.setOrigin(win.getSize().x * 0.5f, win.getSize().y * 0.5f);
        win.setPosition(pos.x, pos.y - size.y * 0.5f + segment * i);
        window.draw(win);
    }
}
Barrier::Barrier(float x, float y) : Obstacle(x, y) {
    shape.setSize(sf::Vector2f(80.f, 40.f));
    shape.setFillColor(sf::Color(230, 140, 40));
    shape.setOrigin(40.f, 20.f);
}
Cone::Cone(float x, float y) : Obstacle(x, y) {
    shape.setSize(sf::Vector2f(34.f, 34.f));
    shape.setFillColor(sf::Color(255, 180, 0));
    shape.setOrigin(17.f, 17.f);
}
Fence::Fence(float x, float y) : Obstacle(x, y) {
    shape.setSize(sf::Vector2f(80.f, 55.f));
    shape.setFillColor(sf::Color(230, 230, 240));
    shape.setOrigin(40.f, 27.5f);
}