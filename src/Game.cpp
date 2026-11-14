#include "Game.hpp"
#include "GridPosition.hpp"
#include "Renderer.hpp"

void Game::initialize() {
    board_.setTile(GridPosition{0, 0}, Tile{TileType::Source});
    board_.setTile(GridPosition{3, 0}, Tile{TileType::Mirror});
    board_.setTile(GridPosition{3, 5}, Tile{TileType::Goal});
}

// TODO: Renderer クラスができたらまた変わる
void Game::render() const {
    for (int y = 0; y < Board::SIZE; y++) {
        for (int x = 0; x < Board::SIZE; x++) {
            GridPosition pos = GridPosition{x, y};
            Tile tile = board_.getTile(pos);
            render::drawTile(pos, tile.type);
        }
    }
}
