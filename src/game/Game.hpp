#pragma once

#include "../core/Board.hpp"
#include "../logic/Laser.hpp"
#include "../stage/StageManager.hpp"

class Game {
public:
    void initialize();
    void render() const;
    void update();
    void reStart();
    void gotoNextStage();
    void loadStage(StageId stageId);
    void handleClick(int pixelX, int pixelY);

private:
    StageManager stageManager_;
    StageId currentStageId_ = StageId::Tutorial;

    Board board_; // プレイ中の盤面
    Laser laser_;
    bool cleared_ = false;
};
