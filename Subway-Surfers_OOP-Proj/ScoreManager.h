#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

class ScoreManager {
private:
    float score;
    int highScore;
    sf::Clock scoreClock;

    // HUD visuals
    sf::Font font;
    sf::Text scoreText;
    sf::Text highScoreText;
    bool fontLoaded;

public:
    ScoreManager();
    void addCoinScore();
    void update();
    void render(sf::RenderWindow& window);
    
    void saveHighScore();
    void loadHighScore();
    
    // Getters for menu display
    int getScore() const { return static_cast<int>(score); }
    int getHighScore() const { return highScore; }
    void resetScore() { score = 0.f; scoreClock.restart(); }
};