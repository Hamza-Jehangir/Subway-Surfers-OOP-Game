#pragma once
#include <SFML/Graphics.hpp>
#include "GameList.h"
#include "Obstacles.h"
#include "Coin.h"
#include "PowerUps.h"

class TrackManager {
private:
    GameList<Obstacle*> obstacles;
    GameList<Coin*> coins;
    GameList<PowerUp*> powerups;
    sf::Clock spawnClock;
    const float LEFT_LANE_X = 250.f, MIDDLE_LANE_X = 400.f, RIGHT_LANE_X = 550.f;

public:
    TrackManager();
    ~TrackManager();
    void update();
    void render(sf::RenderWindow& window);
    bool checkObstacleCollision(const sf::FloatRect& bounds);
    bool checkCoinCollision(const sf::FloatRect& bounds);
    PowerType checkPowerUpCollision(const sf::FloatRect& bounds);
    int collectNearbyCoins(const sf::FloatRect& bounds, float magnetRadius);
    void reset();
};