#pragma once

#include "Board.hpp"

class Game {
    public:
        void initialize();
        void render() const;

    private:
        Board board_;
};
