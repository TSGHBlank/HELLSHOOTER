#include <engine.h>
#include "game.h"
#include "entities.h"
#include "helpers.h"
#include "player.h"
#include "boss.h"
#include "projectiles.h"
#include <cmath>

GameState gameState = STATE_MENU;
Player player;
Boss boss;
std::vector<Projectile> projectiles;
int currentLevel = 1;

float screenAnimTime = 0;

// Texture player + all 3 bosses + projectile textures... 
// Audio as well

void startGame() {
    currentLevel = 1;
    setupLevel(currentLevel);
    gameState = STATE_PLAYING;

    // Background audio placeholder
    // backgroundMusic 
    
}

void nextLevel() {
    currentLevel++;

    if(currentLevel > 3) {
        gameState = STATE_WIN;
    } else {
        setupLevel(currentLevel);
        gameState = STATE_PLAYING;
    }
}

void updateScreenAnimation(float dt) {
    screenAnimTime += dt;
}

void drawScreenAnimation() {
    // Screen animation placeholder:
    // can include animation of projectiles if we want, eg explosion animation or trails of flames

    float pulse = std::sin(screenAnimTime * 2.0f) * 20.0f;

    drawCircle(150, 120, 40 + pulse, Color::red);
    drawCircle(1130, 600, 50 - pulse, Color::magenta);
}

void updateMenu() {
    Vec2 startButtonPos = Vec2(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 40);
    Vec2 startButtonSize = Vec2(300, 80);

    if(mouseButtonPressedThisFrame(MOUSE_BUTTON_LEFT)) {
        if(pointInRect(mousePosition(), startButtonPos, startButtonSize)) {
            startGame();
        }
    }

    if(keyPressedThisFrame(KEY_SPACE)) {
        startGame();
    }
}

void updatePlaying(float dt) {
    updatePlayer(dt);
    updateBoss(dt);
    updateProjectiles(dt);

    if(player.health <= 0) {
        gameState = STATE_GAME_OVER;
    }

    if(boss.health <= 0) {
        gameState = STATE_LEVEL_CLEAR;
    }
}

void updateLevelClear() {
    if(keyPressedThisFrame(KEY_SPACE) || mouseButtonPressedThisFrame(MOUSE_BUTTON_LEFT)) {
        nextLevel();
    }
}

void updateGameOver() {
    if(keyPressedThisFrame(KEY_SPACE) || mouseButtonPressedThisFrame(MOUSE_BUTTON_LEFT)) {
        gameState = STATE_MENU;
    }
}

void updateWin() {
    if(keyPressedThisFrame(KEY_SPACE) || mouseButtonPressedThisFrame(MOUSE_BUTTON_LEFT)) {
        gameState = STATE_MENU;
    }
}

void renderMenu() {
    clear(Color::black);

    drawScreenAnimation();

    drawText(550, 160, "HELLSHOOTER", 255, 255, 255, 255);
    drawText(430, 210, "WASD = Move | Mouse = Aim | Left Click = Shoot", 180, 180, 180, 255);

    Vec2 startButtonPos = Vec2(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 40);
    Vec2 startButtonSize = Vec2(300, 80);

    fillRect(startButtonPos, startButtonSize, Color::blue);
    drawRect(startButtonPos, startButtonSize, Color::white);

    drawText(startButtonPos.x + 95, startButtonPos.y + 32, "START GAME", 255, 255, 255, 255);

    drawText(450, 500, "Audio placeholder area:", 180, 180, 180, 255);
    drawText(450, 530, "Load menu music or button sounds in initGame()", 180, 180, 180, 255);
}

// Just a simple screen text for hp etc can change if we have plenty of time, make it look better 
void renderPlaying() {
    clear(Color::black);

    drawScreenAnimation();

    drawText(20, 20, "Level:", 255, 255, 255, 255);

    if(currentLevel == 1) {
        drawText(80, 20, "1", 255, 255, 255, 255);
    }

    if(currentLevel == 2) {
        drawText(80, 20, "2", 255, 255, 255, 255);
    }

    if(currentLevel == 3) {
        drawText(80, 20, "3", 255, 255, 255, 255);
    }

    drawText(20, 50, "Player Health", 255, 255, 255, 255);
    drawHealthBar(20, 75, 250, 20, player.health, 100);

    drawText(500, 20, "Boss Health", 255, 255, 255, 255);
    drawHealthBar(500, 45, 300, 20, boss.health, boss.maxHealth);

    drawBoss();
    drawPlayer();
    drawProjectiles();
}

// Here we can change the boss hp bar and make it look less generic.

void renderLevelClear() {
    clear(Color::black);

    drawScreenAnimation();

    drawText(530, 280, "BOSS DEFEATED", 255, 255, 255, 255);

    if(currentLevel < 3) {
        drawText(470, 330, "Press SPACE or CLICK for next level", 200, 200, 200, 255);
    } else {
        drawText(500, 330, "Press SPACE or CLICK to finish", 200, 200, 200, 255);
    }
}

void renderGameOver() {
    clear(Color::black);

    drawScreenAnimation();

    drawText(570, 280, "GAME OVER", 255, 0, 0, 255);
    drawText(470, 330, "Press SPACE or CLICK to return to menu", 200, 200, 200, 255);
}

void renderWin() {
    clear(Color::black);

    drawScreenAnimation();

    drawText(520, 280, "YOU DEFEATED ALL BOSSES", 255, 255, 255, 255);
    drawText(470, 330, "Press SPACE or CLICK to return to menu", 200, 200, 200, 255);
}

void initGame() {
    setWindowTitle("HellShooter");
    setWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    setTargetFPS(60);

    // Sprite loading placeholder:
    // playerTexture/ boss (1,2,3) Textures / Player + boss Projectiles textures) add anymore you deem we may need.
  
    // Audio loading placeholder:
    // playerShootSound/bossShootSound/bigShotSound/hitSound/
    // we can add background music here, can have 1 sound track for all levels but if needed we can add 3 different ones for each lvl.

    gameState = STATE_MENU;
}

void updateGame(float dt) {
    updateScreenAnimation(dt);

    if(gameState == STATE_MENU) {
        updateMenu();
    } else if(gameState == STATE_PLAYING) {
        updatePlaying(dt);
    } else if(gameState == STATE_LEVEL_CLEAR) {
        updateLevelClear();
    } else if(gameState == STATE_GAME_OVER) {
        updateGameOver();
    } else if(gameState == STATE_WIN) {
        updateWin();
    }
}

void renderGame(float lag) {
    if(gameState == STATE_MENU) {
        renderMenu();
    } else if(gameState == STATE_PLAYING) {
        renderPlaying();
    } else if(gameState == STATE_LEVEL_CLEAR) {
        renderLevelClear();
    } else if(gameState == STATE_GAME_OVER) {
        renderGameOver();
    } else if(gameState == STATE_WIN) {
        renderWin();
    }
}

void closeGame() {

}