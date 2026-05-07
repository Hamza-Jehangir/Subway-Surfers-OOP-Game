#include "PowerUps.h"
#include <iostream>

PowerUp::PowerUp(float x, float y) {
    speed = 7.0f;
    sprite.setPosition(x, y);
}

void PowerUp::update() { sprite.move(0, speed); }
void PowerUp::draw(sf::RenderWindow& w) { w.draw(sprite); }
sf::FloatRect PowerUp::getBounds() const { return sprite.getGlobalBounds(); }
PowerType PowerUp::getType() const { return type; }

// --- Subclasses Loading Images ---

ShieldPower::ShieldPower(float x, float y) : PowerUp(x, y) {
    type = SHIELD;
    // Load image (Ensure shield.png is in the folder)
    if(texture.loadFromFile("shield.png")) {
        sprite.setTexture(texture);
        // Optional: Scale if image is too big. Adjust 0.1f as needed.
        sprite.setScale(0.2f, 0.2f); 
    }
    // Fallback if image fails: Green Square
    else {
        std::cout << "Failed to load shield.png" << std::endl;
        sprite.setTextureRect(sf::IntRect(0,0,30,30));
        sprite.setColor(sf::Color::Green);
    }
}

MagnetPower::MagnetPower(float x, float y) : PowerUp(x, y) {
    type = MAGNET;
    // You asked for NorthSouth for one of them, using it for Magnet
    if(texture.loadFromFile("NorthSouth.png")) {
        sprite.setTexture(texture);
        sprite.setScale(0.2f, 0.2f);
    }
}

DoubleCoinPower::DoubleCoinPower(float x, float y) : PowerUp(x, y) {
    type = DOUBLE_COIN;
    if(texture.loadFromFile("doubleCoins.png")) {
        sprite.setTexture(texture);
        sprite.setScale(0.2f, 0.2f);
    }
}

JetpackPower::JetpackPower(float x, float y) : PowerUp(x, y) {
    type = JETPACK;
    if(texture.loadFromFile("jetPack.png")) {
        sprite.setTexture(texture);
        sprite.setScale(0.2f, 0.2f);
    }
}
