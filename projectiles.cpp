#include "projectiles.h"
#include "helpers.h"
#include <algorithm>

void addProjectile(
    Vec2 pos,
    Vec2 direction,
    float speed,
    float radius,
    ProjectileOwner owner,
    int damage,
    bool bigProjectile,
    int bouncesLeft
) {
    Projectile p;

    p.pos = pos;
    p.vel = safeUnit(direction) * speed;
    p.radius = radius;
    p.owner = owner;
    p.damage = damage;
    p.alive = true;
    p.bigProjectile = bigProjectile;
    p.bouncesLeft = bouncesLeft;
    p.age = 0;

    projectiles.push_back(p);

    // Audio placeholder:
   
}

void handleBigProjectileBounce(Projectile &p) {
    bool bounced = false;

    if(p.pos.x - p.radius < 0) {
        p.pos.x = p.radius;
        p.vel.x *= -1;
        bounced = true;
    }

    if(p.pos.x + p.radius > SCREEN_WIDTH) {
        p.pos.x = SCREEN_WIDTH - p.radius;
        p.vel.x *= -1;
        bounced = true;
    }

    if(p.pos.y - p.radius < 0) {
        p.pos.y = p.radius;
        p.vel.y *= -1;
        bounced = true;
    }

    if(p.pos.y + p.radius > SCREEN_HEIGHT) {
        p.pos.y = SCREEN_HEIGHT - p.radius;
        p.vel.y *= -1;
        bounced = true;
    }

    if(bounced) {
        if(p.bouncesLeft > 0) {
            p.bouncesLeft--;
        } else {
            p.alive = false;
        }
    }
}

void updateProjectiles(float dt) {
    for(Projectile &p : projectiles) {
        if(p.alive) {
            p.pos += p.vel * dt;
            p.age += dt;
        }

        if(p.bigProjectile && p.owner == PROJECTILE_BOSS) {
            handleBigProjectileBounce(p);
        } else {
            if(p.pos.x < -50 || p.pos.x > SCREEN_WIDTH + 50 ||
               p.pos.y < -50 || p.pos.y > SCREEN_HEIGHT + 50) {
                p.alive = false;
            }
        }
    }

    for(Projectile &p : projectiles) {
        if(!p.alive) {
            continue;
        }

        if(p.owner == PROJECTILE_PLAYER) {
            if(circleRectCollision(p.pos, p.radius, boss.pos, boss.size)) {
                p.alive = false;
                boss.health -= p.damage;

                // Audio placeholder:
                
            }
        } else {
            if(circleRectCollision(p.pos, p.radius, player.pos, player.size)) {
                p.alive = false;
                player.health -= p.damage;

                // Audio placeholder:
                
            }
        }
    }

    projectiles.erase(
        std::remove_if(
            projectiles.begin(),
            projectiles.end(),
            [](Projectile p) {
                return !p.alive;
            }
        ),
        projectiles.end()
    );
}

void drawProjectiles() {
    for(Projectile &p : projectiles) {

        // Projectile sprite animation placeholder:
      
        if(p.bigProjectile) {
            fillCircle(p.pos, p.radius, Color::yellow);
            drawCircle(p.pos, p.radius, Color::red);
        } else if(p.owner == PROJECTILE_PLAYER) {
            fillCircle(p.pos, p.radius, Color::cyan);
        } else {
            fillCircle(p.pos, p.radius, Color::red);
        }
    }
}