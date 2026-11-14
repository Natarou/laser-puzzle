#include "Game.hpp"
#include <emscripten/emscripten.h>

// クリック後にも使えるように、main の外に置く
Game game;

// クリック時に JS から呼び出す関数
extern "C" {
    EMSCRIPTEN_KEEPALIVE void handleClick(int pixelX, int pixelY) {
        game.handleClick(pixelX, pixelY);
    }
}

int main() {
    game.initialize();
    game.update();
    game.render();

    return 0;
}
