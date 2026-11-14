#pragma once

#include "../core/Board.hpp"
#include "../core/GridPosition.hpp"
#include <initializer_list>

struct TilePlacement {
    GridPosition position;
    Tile tile;
};

class Stage {
public:
    Stage(std::initializer_list<TilePlacement> placements);

    bool isValid() const;
    const Board &getInitialBoard() const;

private:
    Board initialBoard_;
    bool valid_ = false;
};
