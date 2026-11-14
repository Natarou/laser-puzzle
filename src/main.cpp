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

// リスタート
extern "C" {
    EMSCRIPTEN_KEEPALIVE void restartGame() {
        game.reStart();
    }
}


// 次ステージに行く
extern "C" {
    EMSCRIPTEN_KEEPALIVE void gotoNextStage() {
        game.gotoNextStage();
    }
}


int main() {
    game.initialize();
    game.update();
    game.render();

    return 0;
}
