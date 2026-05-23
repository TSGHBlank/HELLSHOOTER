#ifndef PROJECTILES_H
#define PROJECTILES_H

#include "entities.h"

void addProjectile(
    Vec2 pos,
    Vec2 direction,
    float speed,
    float radius,
    ProjectileOwner owner,
    int damage = 10,
    bool bigProjectile = false,
    int bouncesLeft = 0
);

void updateProjectiles(float dt);
void drawProjectiles();

#endif