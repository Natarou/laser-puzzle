#pragma once

#include "Board.hpp"
#include "GridPosition.hpp"
#include <vector>

namespace render {
    constexpr int CELL_SIZE = 50; // コンパイル時に値を評価できるため constexpr

    void drawTile(GridPosition pos, Tile tile);
    void drawLaser(const std::vector<GridPosition> &path);
    void drawClearEffect(); // クリア時の文字とか
    GridPosition convertPixelToGridPos(int pixelX, int pixelY);
} // namespace render
