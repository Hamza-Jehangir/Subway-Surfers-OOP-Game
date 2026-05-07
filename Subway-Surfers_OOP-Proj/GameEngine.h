#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "Player.h"
#include "TrackManager.h"
#include "ScoreManager.h"

// Define Game States
enum GameState { MENU, PLAYING, GAME_OVER };

class GameEngine {
private:
    sf::RenderWindow window;
    Player player;
    TrackManager trackManager;
    ScoreManager scoreManager;
    bool isGameOver;
    bool hasShield;
    bool hasJetpack;
    bool hasMagnet;
    sf::Clock powerUpTimer;
    sf::Clock magnetTimer;
    sf::Clock menuAnimationClock;

    // Background visuals
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool hasBackgroundTexture;
    
    // --- POLICE ADDITION ---
    sf::Texture policeTexture;
    sf::Sprite policeSprite;

    // Track graphics textures
    sf::Texture trackTexture;
    sf::Texture sandTexture;
    sf::Texture grassTexture;
    sf::Sprite trackSprite;
    sf::Sprite sandSprite;
    sf::Sprite grassSprite;
    
    // Helper methods for creating textures
    void createTrackTexture();
    void createSandTexture();
    void createGrassTexture();
    void renderTracksBackground(sf::RenderWindow& window);

    // Game State & Music
    GameState currentState;
    sf::Music bgMusic;
    
    // Menu UI
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;
    sf::Text exitText;
    
    // Fancy menu elements
    sf::RectangleShape startButton;
    sf::RectangleShape exitButton;
    sf::Text startButtonText;
    sf::Text exitButtonText;
    bool startButtonHovered;
    bool exitButtonHovered;
    
    // Game Over menu elements
    sf::RectangleShape gameOverPanel;
    sf::Text gameOverTitle;
    sf::Text finalScoreText;
    sf::Text highScoreText;
    sf::RectangleShape restartButton;
    sf::RectangleShape menuButton;
    sf::Text restartButtonText;
    sf::Text menuButtonText;
    bool restartButtonHovered;
    bool menuButtonHovered;
    
    // Animation
    float titlePulseOffset;
    
    // Helper methods
    void resetGame();
    void updateMenuAnimations();
    void renderStartMenu();
    void renderGameOverMenu();

    void processEvents();
    void update();
    void render();

public:
    GameEngine();
    void run();
};
