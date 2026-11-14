#include <emscripten/emscripten.h>

// ステージ番号を書き換える
EM_JS(void, jsShowStageNum, (int stageNum), {
    const element = document.getElementById("stage-num");
    element.textContent = stageNum;
});

namespace ui {
    void showStageNum(int stageNum) {
        jsShowStageNum(stageNum);
    }
}
