#include <emscripten/emscripten.h>

// ステージ番号を書き換える
EM_JS(void, jsShowStageNum, (int stageNum), {
    const element = document.getElementById("stage-num");
    element.textContent = stageNum;
});

// 次ステージボタンの表示切り替え
EM_JS(void, jsSetNextStageButtonVisible, (bool visible), {
    const button = document.getElementById("next-stage-button");
    button.hidden = !visible; // 隠すやつだから真偽値逆になる
});

namespace ui {
    void showStageNum(int stageNum) {
        jsShowStageNum(stageNum);
    }

    void setNextStageButtonVisible(bool visible) {
        jsSetNextStageButtonVisible(visible);
    }
}
