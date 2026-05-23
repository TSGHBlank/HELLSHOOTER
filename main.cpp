#include <engine.h>
#include "game.h"

void init() {
    initGame();
}

void update(float dt) {
    updateGame(dt);
}

void render(float lag) {
    renderGame(lag);
}

void close() {
    closeGame();
}