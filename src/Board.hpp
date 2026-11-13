#pragma once

#include <array>

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

    static constexpr int SIZE = 6; // 盤面の一辺のサイズ

    Tile getTile(GridPosition pos) const; // 読み取るだけで、変更しないので const
    void setTile(GridPosition pos, Tile tile);
    bool isInsideGrid(GridPosition pos) const; // 指定座標が盤面内か

private:
    // TileType を要素に持つ二次元配列のメンバ変数
    // std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE> tiles_; // メンバ変数は末尾に _ を付ける

    // 型に名前を付けて読みやすく
    using Row = std::array<Tile, SIZE>; // 行
    using Grid = std::array<Row, SIZE>; // 盤面全体

    Grid tiles_;
};
