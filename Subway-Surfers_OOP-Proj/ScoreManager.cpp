#include "ScoreManager.h"
#include <iostream> // Added for console output
#include <string>

ScoreManager::ScoreManager() {
    score = 0.f;
    highScore = 0;
    fontLoaded = false;

    loadHighScore();

    // Try to load a modern HUD font. Place "Roboto-Bold.ttf" next to the executable,
    // or change the filename below to match your font.
    if (font.loadFromFile("Roboto-Bold.ttf")) {
        fontLoaded = true;

        scoreText.setFont(font);
        highScoreText.setFont(font);

        scoreText.setCharacterSize(26);
        highScoreText.setCharacterSize(20);

        scoreText.setFillColor(sf::Color::White);
        highScoreText.setFillColor(sf::Color(220, 220, 240));

        scoreText.setOutlineThickness(2.f);
        scoreText.setOutlineColor(sf::Color(0, 0, 0, 160));
        highScoreText.setOutlineThickness(2.f);
        highScoreText.setOutlineColor(sf::Color(0, 0, 0, 160));

        scoreText.setPosition(20.f, 18.f);
        highScoreText.setPosition(20.f, 52.f);

        scoreText.setString("Score: 0");
        highScoreText.setString("High: " + std::to_string(highScore));
    }
}

void ScoreManager::addCoinScore() {
    score += 50;
    std::cout << "Coin Collected! Score: " << (int)score << std::endl;

    if (fontLoaded) {
        scoreText.setString("Score: " + std::to_string(static_cast<int>(score)));
    }
}

void ScoreManager::update() {
    // 10 points per second logic [cite: 35]
    if (scoreClock.getElapsedTime().asSeconds() >= 0.1f) {
        score += 1.0f; 
        scoreClock.restart();

        if (fontLoaded) {
            scoreText.setString("Score: " + std::to_string(static_cast<int>(score)));
        }
    }
}

void ScoreManager::render(sf::RenderWindow& window) {
    if (fontLoaded) {
        window.draw(scoreText);
        window.draw(highScoreText);
    }
}

void ScoreManager::saveHighScore() {
    if (score > highScore) {
        highScore = (int)score;
        std::ofstream outFile("highscore.txt");
        if (outFile.is_open()) {
            outFile << highScore;
            outFile.close();
            std::cout << "New High Score Saved: " << highScore << std::endl;

            if (fontLoaded) {
                highScoreText.setString("High: " + std::to_string(highScore));
            }
        }
    }
}

void ScoreManager::loadHighScore() {
    std::ifstream inFile("highscore.txt");
    if (inFile.is_open()) {
        inFile >> highScore;
        inFile.close();
        std::cout << "Loaded High Score: " << highScore << std::endl;

        if (fontLoaded) {
            highScoreText.setString("High: " + std::to_string(highScore));
        }
    }
}