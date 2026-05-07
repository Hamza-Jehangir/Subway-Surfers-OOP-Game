#include "Player.h"
#include <iostream>

Player::Player() {
    bool imageLoaded = true;

    // Load Textures
    if (!runTexture1.loadFromFile("jake1.png")) {
        std::cout << "DEBUG: jake1.png not found! Using Cyan Box." << std::endl;
        runTexture1.create(50, 100);
        imageLoaded = false;
    }
    if (!runTexture2.loadFromFile("jake2.png")) {
        runTexture2.create(50, 100);
    }

    sprite.setTexture(runTexture1);

    // --- SCALING FIX (Keep him small) ---
    sprite.setScale(0.2f, 0.2f);
    // ------------------------------------

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height);
    sprite.setPosition(MIDDLE_LANE_X, GROUND_Y);

    if (!imageLoaded) sprite.setColor(sf::Color::Cyan);
    else sprite.setColor(sf::Color::White);

    currentLane = 1;
    state = RUNNING;
    isTexture1Active = true;
    hasJetpack = false;
    jumpDurationMultiplier = 1.0f;
}

void Player::moveLeft() {
    if (currentLane > 0) {
        currentLane--;
        float newX = (currentLane == 0) ? LEFT_LANE_X : MIDDLE_LANE_X;
        // CRITICAL FIX: Use 'sprite.getPosition().y' instead of GROUND_Y.
        // This ensures that if we are mid-air, we STAY mid-air when moving left.
        sprite.setPosition(newX, sprite.getPosition().y);
    }
}

void Player::moveRight() {
    if (currentLane < 2) {
        currentLane++;
        float newX = (currentLane == 2) ? RIGHT_LANE_X : MIDDLE_LANE_X;
        // CRITICAL FIX: Use current Y position.
        sprite.setPosition(newX, sprite.getPosition().y);
    }
}

void Player::jump() {
    if (state == RUNNING) {
        state = JUMPING;
        sprite.setColor(sf::Color::Yellow);
        actionClock.restart();
    }
}

void Player::slide() {
    if (state == RUNNING) {
        state = SLIDING;
        sprite.setColor(sf::Color::Red);
        sprite.scale(1.0f, 0.5f);
        actionClock.restart();
    }
}

void Player::update() {
    // Animation
    if (state == RUNNING) {
        if (animationClock.getElapsedTime().asSeconds() > 0.15f) {
            isTexture1Active = !isTexture1Active;
            sprite.setTexture(isTexture1Active ? runTexture1 : runTexture2);
            animationClock.restart();
        }
    }

    // Smooth jump arc using a parabola over time [0, JUMP_DURATION * multiplier]
    if (state == JUMPING) {
        float currentJumpDuration = JUMP_DURATION * jumpDurationMultiplier;
        float elapsed = actionClock.getElapsedTime().asSeconds();
        float t = elapsed / currentJumpDuration;

        if (t >= 1.0f) {
            // End of jump: land back on the ground
            state = RUNNING;
            sprite.setColor(sf::Color::White);
            sprite.setPosition(sprite.getPosition().x, GROUND_Y);
        } else {
            // Parabolic arc: height = H * 4 * t * (1 - t)
            // With jetpack, increase max height too
            float heightMultiplier = hasJetpack ? 1.5f : 1.0f;
            float height = JUMP_HEIGHT * heightMultiplier * 4.f * t * (1.f - t);
            sprite.setPosition(sprite.getPosition().x, GROUND_Y - height);
        }
    }

    // Slide Logic
    else if (state == SLIDING) {
        // Ensure we are on the ground while sliding
        sprite.setPosition(sprite.getPosition().x, GROUND_Y);

        if (actionClock.getElapsedTime().asSeconds() > 1.0f) {
            state = RUNNING;
            sprite.setColor(sf::Color::White);
            sprite.scale(1.0f, 2.0f);
        }
    }
    // Normal Running Logic
    else {
        // Ensure we stick to the ground
        sprite.setPosition(sprite.getPosition().x, GROUND_Y);
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

void Player::setJetpack(bool active) {
    hasJetpack = active;
    if (active) {
        jumpDurationMultiplier = 3.0f; // Jump lasts 3x longer
    } else {
        jumpDurationMultiplier = 1.0f; // Normal jump duration
    }
}

void Player::reset() {
    currentLane = 1;
    state = RUNNING;
    isTexture1Active = true;
    hasJetpack = false;
    jumpDurationMultiplier = 1.0f;
    sprite.setPosition(MIDDLE_LANE_X, GROUND_Y);
    sprite.setColor(sf::Color::White);
    sprite.setScale(0.2f, 0.2f);
    sprite.setTexture(runTexture1);
    animationClock.restart();
    actionClock.restart();
}