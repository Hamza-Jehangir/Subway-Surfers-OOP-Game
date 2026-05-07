#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
protected:
    sf::RectangleShape shape;
    float speed;
public:
    Obstacle(float startX, float startY);
    virtual ~Obstacle() {}
    virtual void update();
    virtual void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};

class Train : public Obstacle {
public:
    Train(float x, float y);
    void draw(sf::RenderWindow& window) override;
};
class Barrier : public Obstacle { public: Barrier(float x, float y); };
class Cone : public Obstacle { public: Cone(float x, float y); };
class Fence : public Obstacle { public: Fence(float x, float y); };