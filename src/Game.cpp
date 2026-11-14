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
            render::drawTile(pos, tile);
        }
    }

    // 経路描画
    render::drawLaser(laser_.getPath());
}

void Game::update() {
    cleared_ = false; // クリア状態更新
    LaserResult result = laser_.trace(board_); // 光路計算

    if (result == LaserResult::ReachedGoal) {
        cleared_ = true;
    }
}

// クリックされた時
void Game::handleClick(int pixelX, int pixelY) {
    // 座標変換
    GridPosition clickPos = render::convertPixelToGridPos(pixelX, pixelY);
    if (!board_.isInsideGrid(clickPos))
        return; // 盤面外ならここで終わり

    // 該当マスのタイルを取得
    Tile clickTile = board_.getTile(clickPos);

    // 鏡なら向き替える
    if (clickTile.type != TileType::Mirror)
        return;

    int currentOrientationNum = static_cast<int>(clickTile.orientation);
    clickTile.orientation = static_cast<MirrorOrientation>((currentOrientationNum + 1) % 2);
    board_.setTile(clickPos, clickTile);

    // update(), render() し直す
    this->update();
    this->render();
}
