#pragma once
#include <SFML/Graphics.hpp>
enum PowerType { MAGNET, JETPACK, SHIELD, DOUBLE_COIN };

class PowerUp {
protected: 
    sf::Sprite sprite;       // Changed from Shape to Sprite
    sf::Texture texture;     // Texture to hold the image
    float speed; 
    PowerType type;

public: 
    PowerUp(float x, float y); 
    virtual ~PowerUp() {} 
    virtual void update(); 
    virtual void draw(sf::RenderWindow& w); 
    sf::FloatRect getBounds() const; 
    PowerType getType() const;
};

class ShieldPower : public PowerUp { public: ShieldPower(float x, float y); };
class MagnetPower : public PowerUp { public: MagnetPower(float x, float y); };
class DoubleCoinPower : public PowerUp { public: DoubleCoinPower(float x, float y); };
class JetpackPower : public PowerUp { public: JetpackPower(float x, float y); };
