#pragma once

#include <array>

// コンパイル時に値が決まっている定数
constexpr int BOARD_SIZE = 6;

// タイルの種類
enum class TileType {
    Empty, // 何もない
    Source, // 光源
    Mirror, // 鏡
    Goal, // ゴール
};

// 鏡の向き
enum class MirrorOrientation {
    Slash,
    BackSlash,
};

// タイルそのものを表す構造体
struct Tile {
    TileType type = TileType::Empty;
    MirrorOrientation orientation = MirrorOrientation::Slash;
};


// 座標
struct GridPosition {
    int x;
    int y;
};

// 盤面
class Board {
public:
    Board();

    Tile getTile(GridPosition pos) const; // 読み取るだけで、変更しないので const
    void setTile(GridPosition pos, Tile tile);

private:
    // TileType を要素に持つ二次元配列のメンバ変数
    // std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE> tiles_; // メンバ変数は末尾に _ を付ける

    // 型に名前を付けて読みやすく
    using Row = std::array<Tile, BOARD_SIZE>; // 行
    using Grid = std::array<Row, BOARD_SIZE>; // 盤面全体

    Grid tiles_;
};
