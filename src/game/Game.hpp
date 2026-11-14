#pragma once

#include "../core/Board.hpp"
#include "../logic/Laser.hpp"

class Game {
public:
    void initialize();
    void render() const;
    void update();
    void reStart();
    void gotoNextStage();
    void loadStage(int stageIdx);
    void handleClick(int pixelX, int pixelY);

private:
    Board board_;
    Laser laser_;
    bool cleared_ = false;
    int currentStageIdx_ = 0;
};
