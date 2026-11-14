#include "Game.hpp"

// クリック後にも使えるように、main の外に置く
Game game;

int main() {
    game.initialize();
    game.update();
    game.render();

    return 0;
}
