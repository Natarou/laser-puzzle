#include <Board.hpp>

Board::Board() {
    for (auto& row : tiles_) {
        Tile tile; // new とかしなくていいの？ c++ での構造体の書き方よくわかってない
        tile.type = TileType::Empty; // 省略できる？
        tile.orientation = MirrorOrientation::Slash; // 省略できる？
        row.fill(tile); // fill って何？この関数定義した覚えないけど
    }
}

Tile Board::getTile(Point pos) const {
    // at() は範囲外参照だと例外を投げる
    // TODO: 例外を投げられてもゲームが終わらないようにする
    return tiles_.at(pos.y).at(pos.x);
}

void Board::setTile(Point pos, Tile tile) {
    tiles_.at(pos.y).at(pos.x) = tile;
}
