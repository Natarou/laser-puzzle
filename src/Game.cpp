#include "Game.hpp"

void Game::initialize() {
    board_.setTile(GridPosition{0, 0}, Tile{TileType::Source});
    board_.setTile(GridPosition{3, 0}, Tile{TileType::Mirror});
    board_.setTile(GridPosition{3, 5}, Tile{TileType::Goal});
}

// TODO: Renderer クラスができたらまた変わる
void Game::render() const {
    for (int y = 0; y < Board::SIZE; y++) {
        for (int x = 0; x < Board::SIZE; x++) {
            Tile tile = board_.getTile(GridPosition{x, y});
            drawRect(x, y, static_cast<int>(tile.type)); // ここからだと呼び出せない
        }
    }
}
