#pragma once

#include "Board.hpp"
#include "GridPosition.hpp"
#include <vector>

// 光線の進行方向
enum class Direction {
    Up,
    Right,
    Down,
    Left,
};

// 光線の状態
struct LaserState {
    GridPosition position;
    Direction direction;
};

class Laser {
public:
    void trace(const Board &board);

private:
    // 光線の現在地
    LaserState state_{GridPosition{0, 0}, Direction::Right};

    // 光線通過マスの記録
    std::vector<GridPosition> path_;

    // 次の位置を計算
    GridPosition calcNextPos() const;

    // 鏡に応じて進行方向変更
    void reflect(MirrorOrientation orientation);
};
