#ifndef ENTITIES_H
#define ENTITIES_H

#include <engine.h>
#include <vector>

const int SCREEN_WIDTH = 1720;
const int SCREEN_HEIGHT = 980;

enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_LEVEL_CLEAR,
    STATE_GAME_OVER,
    STATE_WIN
};

enum ProjectileOwner {
    PROJECTILE_PLAYER,
    PROJECTILE_BOSS
};

struct Player {
    Vec2 pos;
    Vec2 size;
    float speed;
    int health;
    float shootCooldown;
};

struct Boss {
    Vec2 pos;
    Vec2 size;
    Vec2 vel;

    int health;
    int maxHealth;

    float coneTimer;
    float bigShotTimer;
    float moveTimer;
};

struct Projectile {
    Vec2 pos;
    Vec2 vel;

    float radius;
    int damage;

    ProjectileOwner owner;

    bool alive;
    bool bigProjectile;

    int bouncesLeft;

    float age; // Animation placeholder for sprite animation...
};

extern GameState gameState;
extern Player player;
extern Boss boss;
extern std::vector<Projectile> projectiles;
extern int currentLevel;

// Sprite placeholders


#endif