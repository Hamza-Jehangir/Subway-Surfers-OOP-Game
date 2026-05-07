#pragma once
#include <SFML/Graphics.hpp>

enum PlayerState { RUNNING, JUMPING, SLIDING };

class Player {
private:
    sf::Sprite sprite;
    sf::Texture runTexture1, runTexture2;
    
    sf::Clock animationClock;
    sf::Clock actionClock;
    bool isTexture1Active;
    
    int currentLane; 
    PlayerState state;
    
    const float LEFT_LANE_X = 250.f;
    const float MIDDLE_LANE_X = 400.f;
    const float RIGHT_LANE_X = 550.f;
    const float GROUND_Y = 500.f; 

    // Jump tuning
    const float JUMP_DURATION = 0.8f;   // seconds
    const float JUMP_HEIGHT  = 160.f;   // pixels
    
    // Jetpack support
    bool hasJetpack;
    float jumpDurationMultiplier;

public:
    Player();
    void update();
    void moveLeft();
    void moveRight();
    void jump();
    void slide();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void setJetpack(bool active);
    void reset();
};