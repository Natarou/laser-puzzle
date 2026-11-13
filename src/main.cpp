#include <emscripten/emscripten.h>

// C++ から呼び出せる JS 関数を定義
// (戻り値の型, 関数名, 引数)
EM_JS(void, drawRect, (int x, int y), {
    // この中は JS
    const canvas = document.getElementById("game");
    const ctx = canvas.getContext("2d");

    ctx.fillStyle = "blue";
    ctx.fillRect(x, y, 50, 50);
});

int main () {
    drawRect(100, 80);

    return 0;
}
