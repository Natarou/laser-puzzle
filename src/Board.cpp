// 自分で作ったヘッダファイルは "" で囲む
#include "Board.hpp"

Board::Board() {
    for (auto& row : tiles_) {
        // fill で全ての要素に同じ値を代入
        row.fill(Tile{}); // {} 付けると初期化された構造体のオブジェクトが得られる
    }
}

Tile Board::getTile(GridPosition pos) const {
    // at() は範囲外参照だと例外を投げる
    // TODO: 例外を投げられてもゲームが終わらないようにする
    return tiles_.at(pos.y).at(pos.x);
}

void Board::setTile(GridPosition pos, Tile tile) {
    tiles_.at(pos.y).at(pos.x) = tile;
}

bool Board::isInsideGrid(GridPosition pos) const {
    return 0 <= pos.x && pos.x < BOARD_SIZE
        && 0 <= pos.y && pos.y < BOARD_SIZE;
}
