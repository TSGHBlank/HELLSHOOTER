#include "player.h"
#include "helpers.h"
#include "projectiles.h"

void keepPlayerOnScreen() {
    if(player.pos.x < 0) {
        player.pos.x = 0;
    }

    if(player.pos.y < 0) {
        player.pos.y = 0;
    }

    if(player.pos.x > SCREEN_WIDTH - player.size.x) {
        player.pos.x = SCREEN_WIDTH - player.size.x;
    }

    if(player.pos.y > SCREEN_HEIGHT - player.size.y) {
        player.pos.y = SCREEN_HEIGHT - player.size.y;
    }
}

void playerShoot() {
    if(player.shootCooldown <= 0) {
        Vec2 aim = mousePosition() - playerCentre();

        addProjectile(playerCentre(), aim, 650, 6, PROJECTILE_PLAYER, 10, false, 0);

        player.shootCooldown = 0.20f;

        // Audio placeholder:
        // playOnce(playerShootSound);
    }
}

void updatePlayer(float dt) {
    Vec2 movement = Vec2(0, 0);

    if(keyIsPressed(KEY_W)) {
        movement.y -= 1;
    }

    if(keyIsPressed(KEY_S)) {
        movement.y += 1;
    }

    if(keyIsPressed(KEY_A)) {
        movement.x -= 1;
    }

    if(keyIsPressed(KEY_D)) {
        movement.x += 1;
    }

    if(lengthSquared(movement) > 0) {
        movement = safeUnit(movement);
    }

    player.pos += movement * player.speed * dt;

    keepPlayerOnScreen();

    player.shootCooldown -= dt;

    if(mouseButtonIsPressed(MOUSE_BUTTON_LEFT)) {
        playerShoot();
    }
}

void drawPlayer() {
    // Player sprite animation placeholder:
    // drawTexture(playerTexture, player.pos, player.size);

    fillRect(player.pos, player.size, Color::blue);

    Vec2 aimDirection = safeUnit(mousePosition() - playerCentre());
    Vec2 aimEnd = playerCentre() + aimDirection * 40;

    drawLine(playerCentre(), aimEnd, Color::white);
}