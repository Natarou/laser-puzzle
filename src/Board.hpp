#pragma once

#include <array>

// コンパイル時に値が決まっている定数
constexpr int BOARD_SIZE = 6;

enum class TileType {
    Empty, // 何もない
    Source, // 光源
    MirrorSlash, // 鏡
    MirrorBackslash, // 逆鏡
    Goal, // ゴール
};

// 座標
struct Point
{
    int x;
    int y;
};

// 盤面
class Board {
public:
    Board();

    TileType getTile(Point pos) const; // 読み取るだけで、変更しないので const
    void setTile(Point pos, TileType type);

private:
    // TileType を要素に持つ二次元配列のメンバ変数
    // std::array<std::array<TileType, BOARD_SIZE>, BOARD_SIZE> tiles_; // メンバ変数は末尾に _ を付ける

    // 型に名前を付けて読みやすく
    using Row = std::array<TileType, BOARD_SIZE>; // 行
    using Glid = std::array<Row, BOARD_SIZE>; // 盤面全体

    Glid tiles_;
};
