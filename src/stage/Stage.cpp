#include "Stage.hpp"

// ステージをセットする
Stage::Stage(std::initializer_list<TilePlacement> placements) {
    //
    bool occupied[Board::SIZE][Board::SIZE] = {};
    valid_ = true;

    int sourceCount = 0;
    int goalCount = 0;

    // 指定されたタイル
    for (const TilePlacement &placement : placements) {
        GridPosition pos = placement.position;
        Tile tile = placement.tile;

        // 範囲外は不正
        if (!initialBoard_.isInsideGrid(pos)) {
            valid_ = false;
            continue;
        }

        // 同じ座標絵の重複配置も不正
        if (occupied[pos.y][pos.x]) {
            valid_ = false;
            continue;
        }

        occupied[pos.y][pos.x] = true;
        initialBoard_.setTile(pos, tile);

        // 主要なタイルの数を数える
        if (tile.type == TileType::Source) {
            sourceCount++;
        } else if (tile.type == TileType::Goal) {
            goalCount++;
        }
    }

    // 光源とゴールの数確認
    if (sourceCount != 1 || goalCount != 1) {
        valid_ = false;
    }
}

// このステージが適切か否か返す
bool Stage::isValid() const {
    return valid_;
}

// ステージがセットされた Board を返す
const Board &Stage::getInitialBoard() const {
    return initialBoard_;
}
