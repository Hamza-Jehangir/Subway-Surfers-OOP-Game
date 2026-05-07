#include "GameEngine.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

GameEngine::GameEngine() {
    window.create(sf::VideoMode(800, 600), "Subway Surfers :>");
    window.setFramerateLimit(60);

    isGameOver = false;
    hasShield = false;
    hasJetpack = false;
    hasMagnet = false;
    currentState = MENU; // Start in Menu mode

    // --- 1. Load Music ---
    if (bgMusic.openFromFile("blaster master - stage 1.wav")) {
        bgMusic.setLoop(true);
        bgMusic.setVolume(50);
        bgMusic.play();
    } else {
        std::cout << "Error: background_music not running!" << std::endl;
    }

    if (!font.loadFromFile("Arial.ttf")) {
        std::cout << "Error: dot ttf not found!" << std::endl;
    }

    // --- 2. Load Police Image ---
    if (!policeTexture.loadFromFile("police.png")) {
        std::cout << "Error: police.png not found!" << std::endl;
        // Fallback: Red square if image missing
        policeSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
        policeSprite.setColor(sf::Color::Red);
    } else {
        policeSprite.setTexture(policeTexture);
        policeSprite.setScale(0.2f, 0.2f);
        
        sf::FloatRect bounds = policeSprite.getLocalBounds();
        policeSprite.setOrigin(bounds.width / 2.f, 0.f);
    }

    // Initialize menu animation
    titlePulseOffset = 0.f;
    startButtonHovered = false;
    exitButtonHovered = false;
    restartButtonHovered = false;
    menuButtonHovered = false;

    // Fancy Start Menu Setup
    titleText.setFont(font);
    titleText.setString("subway surfers :>");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color(255, 215, 0)); // Gold color
    titleText.setOutlineThickness(3.f);
    titleText.setOutlineColor(sf::Color(139, 0, 0)); // Dark red outline
    titleText.setPosition(400, 120);
    titleText.setOrigin(titleText.getLocalBounds().width / 2.f, titleText.getLocalBounds().height / 2.f);

    // Start Button
    startButton.setSize(sf::Vector2f(250, 60));
    startButton.setFillColor(sf::Color(34, 139, 34)); // Forest green
    startButton.setOutlineThickness(3.f);
    startButton.setOutlineColor(sf::Color(0, 100, 0));
    startButton.setPosition(400, 280);
    startButton.setOrigin(125, 30);

    startButtonText.setFont(font);
    startButtonText.setString("START GAME");
    startButtonText.setCharacterSize(28);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(400, 280);
    startButtonText.setOrigin(startButtonText.getLocalBounds().width / 2.f, startButtonText.getLocalBounds().height / 2.f + 10);

    // Exit Button
    exitButton.setSize(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color(220, 20, 60)); // Crimson
    exitButton.setOutlineThickness(3.f);
    exitButton.setOutlineColor(sf::Color(139, 0, 0));
    exitButton.setPosition(400, 360);
    exitButton.setOrigin(100, 25);

    exitButtonText.setFont(font);
    exitButtonText.setString("EXIT");
    exitButtonText.setCharacterSize(24);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setPosition(400, 360);
    exitButtonText.setOrigin(exitButtonText.getLocalBounds().width / 2.f, exitButtonText.getLocalBounds().height / 2.f + 8);

    // Game Over Menu Setup
    gameOverPanel.setSize(sf::Vector2f(500, 400));
    gameOverPanel.setFillColor(sf::Color(20, 20, 40, 240)); // Dark blue with transparency
    gameOverPanel.setOutlineThickness(4.f);
    gameOverPanel.setOutlineColor(sf::Color(255, 215, 0));
    gameOverPanel.setPosition(400, 300);
    gameOverPanel.setOrigin(250, 200);

    gameOverTitle.setFont(font);
    gameOverTitle.setString("GAME OVER");
    gameOverTitle.setCharacterSize(50);
    gameOverTitle.setFillColor(sf::Color(255, 69, 0)); // Red-orange
    gameOverTitle.setOutlineThickness(2.f);
    gameOverTitle.setOutlineColor(sf::Color::Black);
    gameOverTitle.setPosition(400, 180);
    gameOverTitle.setOrigin(gameOverTitle.getLocalBounds().width / 2.f, gameOverTitle.getLocalBounds().height / 2.f);

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(32);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition(400, 250);

    highScoreText.setFont(font);
    highScoreText.setCharacterSize(28);
    highScoreText.setFillColor(sf::Color(255, 215, 0)); // Gold
    highScoreText.setPosition(400, 300);

    // Restart Button
    restartButton.setSize(sf::Vector2f(200, 50));
    restartButton.setFillColor(sf::Color(34, 139, 34));
    restartButton.setOutlineThickness(3.f);
    restartButton.setOutlineColor(sf::Color(0, 100, 0));
    restartButton.setPosition(400, 380);
    restartButton.setOrigin(100, 25);

    restartButtonText.setFont(font);
    restartButtonText.setString("RESTART");
    restartButtonText.setCharacterSize(24);
    restartButtonText.setFillColor(sf::Color::White);
    restartButtonText.setPosition(400, 380);
    restartButtonText.setOrigin(restartButtonText.getLocalBounds().width / 2.f, restartButtonText.getLocalBounds().height / 2.f + 8);

    // Menu Button (in game over screen)
    menuButton.setSize(sf::Vector2f(200, 50));
    menuButton.setFillColor(sf::Color(70, 130, 180)); // Steel blue
    menuButton.setOutlineThickness(3.f);
    menuButton.setOutlineColor(sf::Color(25, 25, 112));
    menuButton.setPosition(400, 450);
    menuButton.setOrigin(100, 25);

    menuButtonText.setFont(font);
    menuButtonText.setString("MAIN MENU");
    menuButtonText.setCharacterSize(24);
    menuButtonText.setFillColor(sf::Color::White);
    menuButtonText.setPosition(400, 450);
    menuButtonText.setOrigin(menuButtonText.getLocalBounds().width / 2.f, menuButtonText.getLocalBounds().height / 2.f + 8);

    // Background setup
    hasBackgroundTexture = backgroundTexture.loadFromFile("background.png");
    if (hasBackgroundTexture) {
        backgroundSprite.setTexture(backgroundTexture);
        sf::Vector2u texSize = backgroundTexture.getSize();
        sf::Vector2u winSize = window.getSize();
        backgroundSprite.setScale(
            static_cast<float>(winSize.x) / texSize.x,
            static_cast<float>(winSize.y) / texSize.y
        );
    }
    
    // Create procedural textures for tracks, sand, and grass
    createTrackTexture();
    createSandTexture();
    createGrassTexture();
}

void GameEngine::run() {
    while (window.isOpen()) {
        processEvents();
        
        if (currentState == PLAYING && !isGameOver) {
            update();
        }
        
        if (currentState == MENU || currentState == GAME_OVER) {
            updateMenuAnimations();
        }
        
        render();
    }
}

void GameEngine::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            scoreManager.saveHighScore();
            window.close();
        }

        // --- MENU LOGIC ---
        if (currentState == MENU) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            
            // Hover detection
            startButtonHovered = startButton.getGlobalBounds().contains(mousePosF);
            exitButtonHovered = exitButton.getGlobalBounds().contains(mousePosF);
            
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (startButton.getGlobalBounds().contains(mousePosF)) {
                        resetGame();
                        currentState = PLAYING;
                    }
                    if (exitButton.getGlobalBounds().contains(mousePosF)) {
                        window.close();
                    }
                }
            }
        }
        
        // --- GAME OVER MENU LOGIC ---
        if (currentState == GAME_OVER) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            
            // Hover detection
            restartButtonHovered = restartButton.getGlobalBounds().contains(mousePosF);
            menuButtonHovered = menuButton.getGlobalBounds().contains(mousePosF);
            
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (restartButton.getGlobalBounds().contains(mousePosF)) {
                        resetGame();
                        currentState = PLAYING;
                    }
                    if (menuButton.getGlobalBounds().contains(mousePosF)) {
                        resetGame();
                        currentState = MENU;
                    }
                }
            }
        }

        // --- GAME LOGIC ---
        if (currentState == PLAYING && event.type == sf::Event::KeyPressed && !isGameOver) {
            if (event.key.code == sf::Keyboard::A) player.moveLeft();
            else if (event.key.code == sf::Keyboard::D) player.moveRight();
            else if (event.key.code == sf::Keyboard::W) player.jump();
            else if (event.key.code == sf::Keyboard::S) player.slide();
        }
    }
}

void GameEngine::update() {
    player.update();
    
    // --- Update Police Position ---
    sf::FloatRect pBounds = player.getBounds();
    policeSprite.setPosition(pBounds.left, pBounds.top + 150.f);
    
    trackManager.update();
    scoreManager.update();

    if (trackManager.checkCoinCollision(player.getBounds())) {
        scoreManager.addCoinScore();
    }

    PowerType p = trackManager.checkPowerUpCollision(player.getBounds());
    if ((int)p != -1) {
        if (p == SHIELD) {
            hasShield = true;
            powerUpTimer.restart();
            std::cout << "Shield Activated!" << std::endl;
        }
        else if (p == JETPACK) {
            hasJetpack = true;
            player.setJetpack(true);
            powerUpTimer.restart();
            std::cout << "Jetpack Activated!" << std::endl;
        }
        else if (p == MAGNET) {
            hasMagnet = true;
            magnetTimer.restart();
            std::cout << "Magnet Activated!" << std::endl;
        }
    }

    // Update power-up timers
    if (hasShield && powerUpTimer.getElapsedTime().asSeconds() > 5.0f) {
        hasShield = false;
        std::cout << "Shield Expired." << std::endl;
    }
    
    if (hasJetpack && powerUpTimer.getElapsedTime().asSeconds() > 8.0f) {
        hasJetpack = false;
        player.setJetpack(false);
        std::cout << "Jetpack Expired." << std::endl;
    }
    
    // Magnet auto-collects nearby coins
    if (hasMagnet) {
        if (magnetTimer.getElapsedTime().asSeconds() > 10.0f) {
            hasMagnet = false;
            std::cout << "Magnet Expired." << std::endl;
        } else {
            // Collect coins within 200 pixel radius
            int coinsCollected = trackManager.collectNearbyCoins(player.getBounds(), 200.0f);
            if (coinsCollected > 0) {
                for (int i = 0; i < coinsCollected; i++) {
                    scoreManager.addCoinScore();
                }
                std::cout << "Magnet collected " << coinsCollected << " coin(s)!" << std::endl;
            }
        }
    }

    if (trackManager.checkObstacleCollision(player.getBounds())) {
        if (hasShield) {
            hasShield = false;
            std::cout << "Shield Blocked Hit!" << std::endl;
        } else {
            isGameOver = true;
            currentState = GAME_OVER;
            std::cout << "GAME OVER" << std::endl;
            scoreManager.saveHighScore();
        }
    }
}

void GameEngine::render() {
    window.clear();

    if (currentState == MENU) {
        renderStartMenu();
    } 
    else if (currentState == GAME_OVER) {
        // Draw game in background (faded)
        if (hasBackgroundTexture) {
            backgroundSprite.setColor(sf::Color(100, 100, 100, 200)); // Darken
            window.draw(backgroundSprite);
            backgroundSprite.setColor(sf::Color::White); // Reset
        } else {
            const sf::Vector2u winSize = window.getSize();
            const float laneWidth = winSize.x / 3.f;
            sf::RectangleShape laneBg(sf::Vector2f(laneWidth, static_cast<float>(winSize.y)));
            laneBg.setFillColor(sf::Color(20, 30, 45));
            laneBg.setPosition(0.f, 0.f);
            window.draw(laneBg);
            laneBg.setFillColor(sf::Color(15, 20, 30));
            laneBg.setPosition(laneWidth, 0.f);
            window.draw(laneBg);
            laneBg.setFillColor(sf::Color(20, 30, 45));
            laneBg.setPosition(laneWidth * 2.f, 0.f);
            window.draw(laneBg);
        }
        renderGameOverMenu();
    }
    else {
        // Draw Game
        if (hasBackgroundTexture) {
            window.draw(backgroundSprite);
        } else {
            // Draw train tracks with sand and grass
            renderTracksBackground(window);
        }

        // Render objects
        trackManager.render(window);
        player.draw(window);
        
        // --- Draw Police ---
        window.draw(policeSprite);

        scoreManager.render(window);

        // Visual feedback for power-ups
        sf::FloatRect bounds = player.getBounds();
        sf::Vector2f pos(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        
        if (hasShield) {
            sf::CircleShape aura(32.f);
            aura.setFillColor(sf::Color(0, 255, 120, 90));
            aura.setPosition(pos.x - 10.f, pos.y + 15.f);
            window.draw(aura);
        }
        
        if (hasJetpack) {
            // Draw jetpack flames/particles effect
            sf::CircleShape jetpackEffect(20.f);
            jetpackEffect.setFillColor(sf::Color(255, 100, 0, 150));
            jetpackEffect.setPosition(pos.x - 5.f, pos.y + 30.f);
            window.draw(jetpackEffect);
        }
        
        if (hasMagnet) {
            // Draw magnet field effect (larger radius)
            sf::CircleShape magnetField(200.f);
            magnetField.setFillColor(sf::Color(255, 200, 0, 40));
            magnetField.setOutlineThickness(2.f);
            magnetField.setOutlineColor(sf::Color(255, 200, 0, 120));
            magnetField.setOrigin(200.f, 200.f);
            magnetField.setPosition(pos.x, pos.y);
            window.draw(magnetField);
        }
    }

    window.display();
}

void GameEngine::resetGame() {
    isGameOver = false;
    hasShield = false;
    hasJetpack = false;
    hasMagnet = false;
    scoreManager.resetScore();
    player.reset(); // Reset player state
    trackManager.reset(); // Reset track manager
}

void GameEngine::updateMenuAnimations() {
    float time = menuAnimationClock.getElapsedTime().asSeconds();
    titlePulseOffset = sin(time * 2.0f) * 5.0f; // Pulsing animation
}

void GameEngine::renderStartMenu() {
    // Animated gradient background
    sf::RectangleShape bg(sf::Vector2f(800, 600));
    float time = menuAnimationClock.getElapsedTime().asSeconds();
    int r = static_cast<int>(128 + 50 * sin(time * 0.5f));
    int g = static_cast<int>(128 + 50 * sin(time * 0.5f + 2.0f));
    int b = static_cast<int>(128 + 50 * sin(time * 0.5f + 4.0f));
    bg.setFillColor(sf::Color(r, g, b, 255));
    window.draw(bg);

    // Decorative elements - animated circles
    for (int i = 0; i < 5; i++) {
        sf::CircleShape circle(30 + i * 10);
        circle.setFillColor(sf::Color(255, 255, 255, 30));
        circle.setPosition(100 + i * 150, 100 + sin(time + i) * 20);
        window.draw(circle);
    }

    // Title with pulse animation
    titleText.setPosition(400, 120 + titlePulseOffset);
    titleText.setScale(1.0f + sin(time * 1.5f) * 0.05f, 1.0f + sin(time * 1.5f) * 0.05f);
    window.draw(titleText);

    // Buttons with hover effects
    if (startButtonHovered) {
        startButton.setFillColor(sf::Color(50, 205, 50)); // Lime green
        startButton.setScale(1.05f, 1.05f);
        startButtonText.setCharacterSize(30);
    } else {
        startButton.setFillColor(sf::Color(34, 139, 34)); // Forest green
        startButton.setScale(1.0f, 1.0f);
        startButtonText.setCharacterSize(28);
    }
    window.draw(startButton);
    startButtonText.setOrigin(startButtonText.getLocalBounds().width / 2.f, startButtonText.getLocalBounds().height / 2.f + 10);
    window.draw(startButtonText);

    if (exitButtonHovered) {
        exitButton.setFillColor(sf::Color(255, 20, 147)); // Deep pink
        exitButton.setScale(1.05f, 1.05f);
        exitButtonText.setCharacterSize(26);
    } else {
        exitButton.setFillColor(sf::Color(220, 20, 60)); // Crimson
        exitButton.setScale(1.0f, 1.0f);
        exitButtonText.setCharacterSize(24);
    }
    window.draw(exitButton);
    exitButtonText.setOrigin(exitButtonText.getLocalBounds().width / 2.f, exitButtonText.getLocalBounds().height / 2.f + 8);
    window.draw(exitButtonText);

    // Instructions text
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Use A/D to move, W to jump, S to slide");
    instructions.setCharacterSize(18);
    instructions.setFillColor(sf::Color(255, 255, 255, 200));
    instructions.setPosition(400, 500);
    instructions.setOrigin(instructions.getLocalBounds().width / 2.f, instructions.getLocalBounds().height / 2.f);
    window.draw(instructions);
}

void GameEngine::renderGameOverMenu() {
    // Semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    // Game Over Panel
    float time = menuAnimationClock.getElapsedTime().asSeconds();
    gameOverPanel.setScale(1.0f + sin(time * 2.0f) * 0.02f, 1.0f + sin(time * 2.0f) * 0.02f);
    window.draw(gameOverPanel);

    // Game Over Title with pulse
    gameOverTitle.setPosition(400, 180 + sin(time * 3.0f) * 3.0f);
    window.draw(gameOverTitle);

    // Score display
    int finalScore = scoreManager.getScore();
    int highScore = scoreManager.getHighScore();
    finalScoreText.setString("Final Score: " + std::to_string(finalScore));
    finalScoreText.setOrigin(finalScoreText.getLocalBounds().width / 2.f, finalScoreText.getLocalBounds().height / 2.f);
    window.draw(finalScoreText);

    highScoreText.setString("High Score: " + std::to_string(highScore));
    highScoreText.setOrigin(highScoreText.getLocalBounds().width / 2.f, highScoreText.getLocalBounds().height / 2.f);
    window.draw(highScoreText);

    // New high score indicator
    if (finalScore == highScore && finalScore > 0) {
        sf::Text newRecord;
        newRecord.setFont(font);
        newRecord.setString("NEW RECORD!");
        newRecord.setCharacterSize(24);
        newRecord.setFillColor(sf::Color(255, 215, 0));
        newRecord.setStyle(sf::Text::Bold);
        newRecord.setPosition(400, 330);
        newRecord.setOrigin(newRecord.getLocalBounds().width / 2.f, newRecord.getLocalBounds().height / 2.f);
        newRecord.setScale(1.0f + sin(time * 4.0f) * 0.1f, 1.0f + sin(time * 4.0f) * 0.1f);
        window.draw(newRecord);
    }

    // Buttons with hover effects
    if (restartButtonHovered) {
        restartButton.setFillColor(sf::Color(50, 205, 50));
        restartButton.setScale(1.05f, 1.05f);
        restartButtonText.setCharacterSize(26);
    } else {
        restartButton.setFillColor(sf::Color(34, 139, 34));
        restartButton.setScale(1.0f, 1.0f);
        restartButtonText.setCharacterSize(24);
    }
    window.draw(restartButton);
    restartButtonText.setOrigin(restartButtonText.getLocalBounds().width / 2.f, restartButtonText.getLocalBounds().height / 2.f + 8);
    window.draw(restartButtonText);

    if (menuButtonHovered) {
        menuButton.setFillColor(sf::Color(100, 149, 237)); // Cornflower blue
        menuButton.setScale(1.05f, 1.05f);
        menuButtonText.setCharacterSize(26);
    } else {
        menuButton.setFillColor(sf::Color(70, 130, 180)); // Steel blue
        menuButton.setScale(1.0f, 1.0f);
        menuButtonText.setCharacterSize(24);
    }
    window.draw(menuButton);
    menuButtonText.setOrigin(menuButtonText.getLocalBounds().width / 2.f, menuButtonText.getLocalBounds().height / 2.f + 8);
    window.draw(menuButtonText);
}

void GameEngine::createTrackTexture() {
    const int trackWidth = 120;
    const int trackHeight = 600;
    
    sf::RenderTexture renderTexture;
    renderTexture.create(trackWidth, trackHeight);
    renderTexture.clear(sf::Color(60, 50, 40)); // Dark brown base
    
    // Draw wooden ties (horizontal planks)
    for (int y = 0; y < trackHeight; y += 40) {
        sf::RectangleShape tie(sf::Vector2f(trackWidth, 8));
        tie.setFillColor(sf::Color(101, 67, 33)); // Brown wood color
        tie.setPosition(0, y);
        renderTexture.draw(tie);
    }
    
    // Draw metal rails (two vertical rails)
    sf::RectangleShape rail1(sf::Vector2f(6, trackHeight));
    rail1.setFillColor(sf::Color(120, 120, 120)); // Silver/gray
    rail1.setPosition(trackWidth * 0.25f, 0);
    renderTexture.draw(rail1);
    
    sf::RectangleShape rail2(sf::Vector2f(6, trackHeight));
    rail2.setFillColor(sf::Color(120, 120, 120)); // Silver/gray
    rail2.setPosition(trackWidth * 0.75f, 0);
    renderTexture.draw(rail2);
    
    // Add some texture details - cross ties connecting rails
    for (int y = 0; y < trackHeight; y += 40) {
        sf::RectangleShape crossTie(sf::Vector2f(trackWidth * 0.5f, 3));
        crossTie.setFillColor(sf::Color(80, 50, 30));
        crossTie.setPosition(trackWidth * 0.25f, y + 4);
        renderTexture.draw(crossTie);
    }
    
    renderTexture.display();
    trackTexture = renderTexture.getTexture();
    trackSprite.setTexture(trackTexture);
}

void GameEngine::createSandTexture() {
    const int sandWidth = 200;  // Make it larger for better tiling
    const int sandHeight = 200;
    
    sf::RenderTexture renderTexture;
    renderTexture.create(sandWidth, sandHeight);
    renderTexture.clear(sf::Color(194, 178, 128)); // Light sandy brown base
    
    // Add some texture variation for sand
    std::srand(42); // Seed for consistency
    for (int y = 0; y < sandHeight; y += 8) {
        for (int x = 0; x < sandWidth; x += 8) {
            int variation = std::rand() % 25;
            sf::RectangleShape grain(sf::Vector2f(6, 6));
            grain.setFillColor(sf::Color(
                std::max(0, 194 - variation),
                std::max(0, 178 - variation),
                std::max(0, 128 - variation)
            ));
            grain.setPosition(x, y);
            renderTexture.draw(grain);
        }
    }
    
    renderTexture.display();
    sandTexture = renderTexture.getTexture();
    sandSprite.setTexture(sandTexture);
}

void GameEngine::createGrassTexture() {
    const int grassWidth = 300;  // Make it larger for better tiling
    const int grassHeight = 300;
    
    sf::RenderTexture renderTexture;
    renderTexture.create(grassWidth, grassHeight);
    renderTexture.clear(sf::Color(34, 139, 34)); // Forest green base
    
    // Add grass texture variation
    std::srand(123); // Seed for consistency
    for (int y = 0; y < grassHeight; y += 12) {
        for (int x = 0; x < grassWidth; x += 12) {
            int variation = std::rand() % 35;
            sf::RectangleShape patch(sf::Vector2f(10, 10));
            patch.setFillColor(sf::Color(
                std::max(0, 34 - variation / 2),
                std::min(255, 139 + variation / 2),
                std::max(0, 34 - variation / 3)
            ));
            patch.setPosition(x, y);
            renderTexture.draw(patch);
        }
    }
    
    // Add some grass blades for detail
    std::srand(456);
    for (int i = 0; i < 300; i++) {
        int x = std::rand() % grassWidth;
        int y = std::rand() % grassHeight;
        int height = 8 + (std::rand() % 12);
        sf::RectangleShape blade(sf::Vector2f(2, height));
        blade.setFillColor(sf::Color(0, 100 + (std::rand() % 60), 0));
        blade.setPosition(x, y);
        renderTexture.draw(blade);
    }
    
    renderTexture.display();
    grassTexture = renderTexture.getTexture();
    grassSprite.setTexture(grassTexture);
}

void GameEngine::renderTracksBackground(sf::RenderWindow& window) {
    const float LEFT_LANE_X = 250.f;
    const float MIDDLE_LANE_X = 400.f;
    const float RIGHT_LANE_X = 550.f;
    const float TRACK_WIDTH = 120.f;
    const float WIN_WIDTH = 800.f;
    const float WIN_HEIGHT = 600.f;
    
    // Calculate positions
    float track1Left = LEFT_LANE_X - TRACK_WIDTH / 2.f;
    float track1Right = LEFT_LANE_X + TRACK_WIDTH / 2.f;
    float track2Left = MIDDLE_LANE_X - TRACK_WIDTH / 2.f;
    float track2Right = MIDDLE_LANE_X + TRACK_WIDTH / 2.f;
    float track3Left = RIGHT_LANE_X - TRACK_WIDTH / 2.f;
    float track3Right = RIGHT_LANE_X + TRACK_WIDTH / 2.f;
    
    // Left grass (from 0 to start of first track)
    float leftGrassWidth = track1Left;
    if (leftGrassWidth > 0) {
        sf::RectangleShape leftGrass(sf::Vector2f(leftGrassWidth, WIN_HEIGHT));
        leftGrass.setPosition(0, 0);
        leftGrass.setTexture(&grassTexture);
        window.draw(leftGrass);
    }
    
    // Track 1
    trackSprite.setPosition(track1Left, 0);
    trackSprite.setScale(1.f, 1.f);
    window.draw(trackSprite);
    
    // Sand between track 1 and 2
    float sand1Width = track2Left - track1Right;
    if (sand1Width > 0) {
        sf::RectangleShape sand1(sf::Vector2f(sand1Width, WIN_HEIGHT));
        sand1.setPosition(track1Right, 0);
        sand1.setTexture(&sandTexture);
        window.draw(sand1);
    }
    
    // Track 2
    trackSprite.setPosition(track2Left, 0);
    window.draw(trackSprite);
    
    // Sand between track 2 and 3
    float sand2Width = track3Left - track2Right;
    if (sand2Width > 0) {
        sf::RectangleShape sand2(sf::Vector2f(sand2Width, WIN_HEIGHT));
        sand2.setPosition(track2Right, 0);
        sand2.setTexture(&sandTexture);
        window.draw(sand2);
    }
    
    // Track 3
    trackSprite.setPosition(track3Left, 0);
    window.draw(trackSprite);
    
    // Right grass (from end of last track to window edge)
    float rightGrassWidth = WIN_WIDTH - track3Right;
    if (rightGrassWidth > 0) {
        sf::RectangleShape rightGrass(sf::Vector2f(rightGrassWidth, WIN_HEIGHT));
        rightGrass.setPosition(track3Right, 0);
        rightGrass.setTexture(&grassTexture);
        window.draw(rightGrass);
    }
}
