#pragma once

#include "Board.hpp"
#include "GridPosition.hpp"
#include <vector>

namespace render {
    const int CELL_SIZE = 50;

    void drawTile(GridPosition pos, TileType type);
    void drawLaser(const std::vector<GridPosition> &path);
} // namespace render
