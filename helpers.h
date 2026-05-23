#ifndef HELPERS_H
#define HELPERS_H

#include "entities.h"

float lengthSquared(Vec2 v);
float distanceSquared(Vec2 a, Vec2 b);
Vec2 safeUnit(Vec2 v);

bool circleCollision(Vec2 a, float radiusA, Vec2 b, float radiusB);
bool circleRectCollision(Vec2 circlePos, float radius, Vec2 rectPos, Vec2 rectSize);
bool pointInRect(Vec2 point, Vec2 rectPos, Vec2 rectSize);

Vec2 playerCentre();
Vec2 bossCentre();

void drawHealthBar(float x, float y, float width, float height, int health, int maxHealth);

#endif