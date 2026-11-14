#pragma once

#include "Stage.hpp"
#include <map>
#include <vector>

enum class StageId {
    Tutorial,
    Reflection,
    Wall,
};

class StageManager {
public:
    StageManager();

    const Stage *findStage(StageId stageId) const;
    StageId getNextStageId(StageId currentStageId) const;
private:
    std::map<StageId, Stage> stages_;
    std::vector<StageId> stageOrder_;
};
