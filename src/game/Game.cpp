#include "Game.hpp"
#include "../core/GridPosition.hpp"
#include "../render/Renderer.hpp"
#include "../render/UI.hpp"

void Game::initialize() {
    loadStage(0);
}

// TODO: Renderer クラスができたらまた変わる
void Game::render() const {
    // ステージ番号描画
    ui::showStageNum(currentStageIdx_ + 1);

    // 盤面描画
    for (int y = 0; y < Board::SIZE; y++) {
        for (int x = 0; x < Board::SIZE; x++) {
            GridPosition pos = GridPosition{x, y};
            Tile tile = board_.getTile(pos);
            render::drawTile(pos, tile);
        }
    }

    // 経路描画
    render::drawLaser(laser_.getPath());

    // クリア描画
    ui::setNextStageButtonVisible(cleared_);
    if (cleared_)
        render::drawClearEffect();
}

void Game::update() {
    cleared_ = false;                          // クリア状態更新
    LaserResult result = laser_.trace(board_); // 光路計算

    cleared_ = (result == LaserResult::ReachedGoal);
}

// リスタート、ステージを初期状態に戻して描画
void Game::reStart() {
    cleared_ = false;
    loadStage(currentStageIdx_);
    update();
    render();
}

// 次のステージに行く
void Game::gotoNextStage() {
    if (!cleared_) return; // クリアしてないと次ステージ進めない
    currentStageIdx_ = (currentStageIdx_ + 1) % 3;
    reStart();
}

// ステージを読み込む
void Game::loadStage(int stageIdx) {
    board_ = Board{};
    // TODO: ゆくゆく Stage としてどこかにまとめたり、編集しやすくしたい
    switch (stageIdx) {
    case 0:
    default:
        board_.setTile(GridPosition{0, 0}, Tile{TileType::Source});
        board_.setTile(GridPosition{3, 0}, Tile{TileType::Mirror});
        board_.setTile(GridPosition{3, 5}, Tile{TileType::Goal});
        break;
    case 1:
        board_.setTile(GridPosition{0, 0}, Tile{TileType::Source});
        board_.setTile(GridPosition{5, 0}, Tile{TileType::Mirror});
        board_.setTile(GridPosition{5, 5}, Tile{TileType::Mirror, MirrorOrientation::BackSlash});
        board_.setTile(GridPosition{0, 5}, Tile{TileType::Goal});
        break;
    case 2:
        board_.setTile(GridPosition{0, 0}, Tile{TileType::Source});
        board_.setTile(GridPosition{5, 0}, Tile{TileType::Mirror});
        board_.setTile(GridPosition{5, 3}, Tile{TileType::Mirror, MirrorOrientation::BackSlash});
        board_.setTile(GridPosition{2, 3}, Tile{TileType::Mirror, MirrorOrientation::BackSlash});
        board_.setTile(GridPosition{2, 4}, Tile{TileType::Mirror, MirrorOrientation::BackSlash});
        board_.setTile(GridPosition{0, 4}, Tile{TileType::Mirror, MirrorOrientation::BackSlash});
        board_.setTile(GridPosition{0, 1}, Tile{TileType::Mirror});
        board_.setTile(GridPosition{4, 1}, Tile{TileType::Mirror});
        board_.setTile(GridPosition{4, 2}, Tile{TileType::Wall});
        board_.setTile(GridPosition{0, 5}, Tile{TileType::Goal});
        break;
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
