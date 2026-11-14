#pragma once

#include "Board.hpp"
#include "Laser.hpp"

class Game {
public:
    void initialize();
    void render() const;
    void update();
    void handleClick(int pixelX, int pixelY);

private:
    Board board_;
    Laser laser_;
    bool cleared_ = false;
};
