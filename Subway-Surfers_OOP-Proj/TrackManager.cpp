#include "TrackManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

TrackManager::TrackManager() {
    std::srand((unsigned)std::time(nullptr));
}

TrackManager::~TrackManager() {
    for (int i=0; i<obstacles.size(); i++) delete obstacles.get(i);
    for (int i=0; i<coins.size(); i++) delete coins.get(i);
    for (int i=0; i<powerups.size(); i++) delete powerups.get(i);
}

void TrackManager::update() {
    // SPAWNING LOGIC (Adjusted to 1.0s for faster testing)
    if (spawnClock.getElapsedTime().asSeconds() > 1.0f) {
        spawnClock.restart();

        int roll = std::rand() % 100;
        int lane = std::rand() % 3;
        // Map lanes to X coordinates
        float x = (lane == 0) ? LEFT_LANE_X : (lane == 1) ? MIDDLE_LANE_X : RIGHT_LANE_X;
       
        // Spawn slightly higher (-150) so they flow in smoothly
        float startY = -150.f;

        if (roll < 60) { // 60% chance for Obstacle
            int t = std::rand() % 4;
            Obstacle* o = nullptr;
            if (t==0) o = new Train(x, startY);
            else if (t==1) o = new Barrier(x, startY);
            else if (t==2) o = new Cone(x, startY);
            else o = new Fence(x, startY);
           
            if (o) {
                if (!obstacles.add(o)) delete o; // Prevent leak if full
            }
        }
        else if (roll < 85) { // 25% chance for Coin
            Coin* c = new Coin(x, startY);
            if (!coins.add(c)) delete c;
        }
        else { // 15% chance for PowerUp
            int t = std::rand() % 4;
            PowerUp* p = nullptr;
            if (t==0) p = new ShieldPower(x, startY);
            else if (t==1) p = new MagnetPower(x, startY);
            else if (t==2) p = new DoubleCoinPower(x, startY);
            else p = new JetpackPower(x, startY);
           
            if (p) {
                if (!powerups.add(p)) delete p;
            }
        }
    }

    // UPDATE & CLEANUP LOOPS
    // 1. Obstacles
    for (int i=0; i<obstacles.size(); ) {
        Obstacle* o = obstacles.get(i);
        if(o) {
            o->update();
            if(o->getBounds().top > 650) { // If off-screen bottom
                delete o;
                obstacles.removeAt(i);
            } else i++;
        } else i++;
    }
   
    // 2. Coins
    for (int i=0; i<coins.size(); ) {
        Coin* c = coins.get(i);
        if(c) {
            c->update();
            if(c->getBounds().top > 650) {
                delete c;
                coins.removeAt(i);
            } else i++;
        } else i++;
    }

    // 3. PowerUps
    for (int i=0; i<powerups.size(); ) {
        PowerUp* p = powerups.get(i);
        if(p) {
            p->update();
            if(p->getBounds().top > 650) {
                delete p;
                powerups.removeAt(i);
            } else i++;
        } else i++;
    }
}

void TrackManager::render(sf::RenderWindow& w) {
    for(int i=0; i<obstacles.size(); i++) if(obstacles.get(i)) obstacles.get(i)->draw(w);
    for(int i=0; i<coins.size(); i++) if(coins.get(i)) coins.get(i)->draw(w);
    for(int i=0; i<powerups.size(); i++) if(powerups.get(i)) powerups.get(i)->draw(w);
}

// Collision functions remain the same...
bool TrackManager::checkObstacleCollision(const sf::FloatRect& b) {
    for(int i=0; i<obstacles.size(); i++)
        if(obstacles.get(i) && obstacles.get(i)->getBounds().intersects(b)) return true;
    return false;
}

bool TrackManager::checkCoinCollision(const sf::FloatRect& b) {
    for(int i=0; i<coins.size(); i++)
        if(coins.get(i) && coins.get(i)->getBounds().intersects(b)) {
            delete coins.get(i);
            coins.removeAt(i);
            return true;
        }
    return false;
}

PowerType TrackManager::checkPowerUpCollision(const sf::FloatRect& b) {
    for(int i=0; i<powerups.size(); i++)
        if(powerups.get(i) && powerups.get(i)->getBounds().intersects(b)) {
            PowerType t = powerups.get(i)->getType();
            delete powerups.get(i);
            powerups.removeAt(i);
            return t;
        }
    return (PowerType)-1;
}

int TrackManager::collectNearbyCoins(const sf::FloatRect& bounds, float magnetRadius) {
    int coinsCollected = 0;
    sf::Vector2f playerCenter(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    );
    
    for(int i=0; i<coins.size(); ) {
        Coin* c = coins.get(i);
        if(c) {
            sf::FloatRect coinBounds = c->getBounds();
            sf::Vector2f coinCenter(
                coinBounds.left + coinBounds.width / 2.f,
                coinBounds.top + coinBounds.height / 2.f
            );
            
            // Calculate distance
            float dx = playerCenter.x - coinCenter.x;
            float dy = playerCenter.y - coinCenter.y;
            float distance = std::sqrt(dx * dx + dy * dy);
            
            // If coin is within magnet radius, collect it
            if(distance <= magnetRadius) {
                delete c;
                coins.removeAt(i);
                coinsCollected++;
            } else {
                i++;
            }
        } else {
            i++;
        }
    }
    
    return coinsCollected;
}

void TrackManager::reset() {
    // Clear all obstacles
    for (int i = 0; i < obstacles.size(); i++) {
        Obstacle* o = obstacles.get(i);
        if (o) delete o;
    }
    obstacles.clear();

    // Clear all coins
    for (int i = 0; i < coins.size(); i++) {
        Coin* c = coins.get(i);
        if (c) delete c;
    }
    coins.clear();

    // Clear all power-ups
    for (int i = 0; i < powerups.size(); i++) {
        PowerUp* p = powerups.get(i);
        if (p) delete p;
    }
    powerups.clear();

    // Reset spawn clock
    spawnClock.restart();
}