#include "helpers.h"

float lengthSquared(Vec2 v) {
    return v.x * v.x + v.y * v.y;
}

float distanceSquared(Vec2 a, Vec2 b) {
    Vec2 diff = a - b;
    return lengthSquared(diff);
}

Vec2 safeUnit(Vec2 v) {
    float len = length(v);

    if(len == 0) {
        return Vec2(0, -1);
    }

    return v / len;
}

bool circleCollision(Vec2 a, float radiusA, Vec2 b, float radiusB) {
    float totalRadius = radiusA + radiusB;
    return distanceSquared(a, b) <= totalRadius * totalRadius;
}

bool circleRectCollision(Vec2 circlePos, float radius, Vec2 rectPos, Vec2 rectSize) {
    float closestX = circlePos.x;
    float closestY = circlePos.y;

    if(closestX < rectPos.x) {
        closestX = rectPos.x;
    }

    if(closestX > rectPos.x + rectSize.x) {
        closestX = rectPos.x + rectSize.x;
    }

    if(closestY < rectPos.y) {
        closestY = rectPos.y;
    }

    if(closestY > rectPos.y + rectSize.y) {
        closestY = rectPos.y + rectSize.y;
    }

    return circleCollision(circlePos, radius, Vec2(closestX, closestY), 0);
}

bool pointInRect(Vec2 point, Vec2 rectPos, Vec2 rectSize) {
    return point.x >= rectPos.x &&
           point.x <= rectPos.x + rectSize.x &&
           point.y >= rectPos.y &&
           point.y <= rectPos.y + rectSize.y;
}

Vec2 playerCentre() {
    return player.pos + player.size / 2.0f;
}

Vec2 bossCentre() {
    return boss.pos + boss.size / 2.0f;
}

void drawHealthBar(float x, float y, float width, float height, int health, int maxHealth) {
    if(health < 0) {
        health = 0;
    }

    float percent = (float)health / (float)maxHealth;
    float fillWidth = width * percent;

    drawRect(x, y, width, height, Color::white);
    fillRect(x, y, fillWidth, height, Color::green);
}