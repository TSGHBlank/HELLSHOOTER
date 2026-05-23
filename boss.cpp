#include "boss.h"
#include "helpers.h"
#include "projectiles.h"
#include <cmath>

const float PI = 3.14159265f;

void setupLevel(int level) {
    projectiles.clear();

    player.pos = Vec2(SCREEN_WIDTH / 2 - 24, SCREEN_HEIGHT - 90);
    player.size = Vec2(48, 48);
    player.speed = 350;
    player.health = 100;
    player.shootCooldown = 0;

    boss.size = Vec2(120, 90);
    boss.pos = Vec2(SCREEN_WIDTH / 2 - boss.size.x / 2, 80);
    boss.moveTimer = 0;
    boss.coneTimer = 7;
    boss.bigShotTimer = 5;

    if(level == 1) {
        boss.health = 120;
        boss.maxHealth = 120;
        boss.vel = safeUnit(Vec2(1, 0.7f)) * 160;
    }

    if(level == 2) {
        boss.health = 170;
        boss.maxHealth = 170;
        boss.vel = safeUnit(Vec2(-1, 0.8f)) * 190;
    }

    if(level == 3) {
        boss.health = 250;
        boss.maxHealth = 250;
        boss.vel = safeUnit(Vec2(1, 1)) * 260;
        boss.coneTimer = 4;
        boss.bigShotTimer = 3;
    }
}

void updateBossMovement(float dt) {
    boss.pos += boss.vel * dt;

    if(boss.pos.x < 40) {
        boss.pos.x = 40;
        boss.vel.x *= -1;
    }

    if(boss.pos.x > SCREEN_WIDTH - boss.size.x - 40) {
        boss.pos.x = SCREEN_WIDTH - boss.size.x - 40;
        boss.vel.x *= -1;
    }

    if(boss.pos.y < 50) {
        boss.pos.y = 50;
        boss.vel.y *= -1;
    }

    if(boss.pos.y > 280) {
        boss.pos.y = 280;
        boss.vel.y *= -1;
    }
}

void shootConeAttack(float projectileSpeed, float cooldown) {
    boss.coneTimer -= cooldown;

   
}

void fireConeProjectiles(float projectileSpeed) {
    Vec2 start = bossCentre();

    addProjectile(start, Vec2(-0.9f, 1), projectileSpeed, 8, PROJECTILE_BOSS, 10);
    addProjectile(start, Vec2(-0.6f, 1), projectileSpeed, 8, PROJECTILE_BOSS, 10);
    addProjectile(start, Vec2(-0.3f, 1), projectileSpeed, 8, PROJECTILE_BOSS, 10);
    addProjectile(start, Vec2(0.0f, 1), projectileSpeed, 8, PROJECTILE_BOSS, 10);
    addProjectile(start, Vec2(0.3f, 1), projectileSpeed, 8, PROJECTILE_BOSS, 10);
    addProjectile(start, Vec2(0.6f, 1), projectileSpeed, 8, PROJECTILE_BOSS, 10);
    addProjectile(start, Vec2(0.9f, 1), projectileSpeed, 8, PROJECTILE_BOSS, 10);

    // Audio placeholder:
   
}

void fireBigBouncingProjectile(float projectileSpeed) {
    Vec2 direction = playerCentre() - bossCentre();

    addProjectile(
        bossCentre(),
        direction,
        projectileSpeed,
        24,
        PROJECTILE_BOSS,
        20,
        true,
        2
    );

    // Audio placeholder:
    
}

void updateBossLevel1(float dt) {
    updateBossMovement(dt);

    boss.coneTimer -= dt;

    if(boss.coneTimer <= 0) {
        fireConeProjectiles(320);
        boss.coneTimer = 7.0f;
    }
}

void updateBossLevel2(float dt) {
    updateBossMovement(dt);

    boss.bigShotTimer -= dt;

    if(boss.bigShotTimer <= 0) {
        fireBigBouncingProjectile(330);
        boss.bigShotTimer = 5.0f;
    }
}

void updateBossLevel3(float dt) {
    updateBossMovement(dt);

    boss.coneTimer -= dt;
    boss.bigShotTimer -= dt;

    if(boss.coneTimer <= 0) {
        fireConeProjectiles(430);
        boss.coneTimer = 4.0f;
    }

    if(boss.bigShotTimer <= 0) {
        fireBigBouncingProjectile(430);
        boss.bigShotTimer = 3.0f;
    }
}

void updateBoss(float dt) {
    if(currentLevel == 1) {
        updateBossLevel1(dt);
    }

    if(currentLevel == 2) {
        updateBossLevel2(dt);
    }

    if(currentLevel == 3) {
        updateBossLevel3(dt);
    }
}

void drawBoss() {
    // Boss sprite animation placeholder:
 

    if(currentLevel == 1) {
        fillRect(boss.pos, boss.size, Color::red);
    }

    if(currentLevel == 2) {
        fillRect(boss.pos, boss.size, Color::magenta);
    }

    if(currentLevel == 3) {
        fillRect(boss.pos, boss.size, Color::yellow);
    }
}