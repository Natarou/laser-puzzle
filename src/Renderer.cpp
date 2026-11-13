#include "Renderer.hpp"
#include <emscripten/emscripten.h>

// C++ から呼び出せる JS 関数を定義
// (戻り値の型, 関数名, 引数)
EM_JS(void, jsDrawTile, (int x, int y, int tileType), {
    // この中は JS
    // TODO: CELL_SIZE を誰が持つかは要検討
    const CELL_SIZE = 50;

    const canvas = document.getElementById("game");
    const ctx = canvas.getContext("2d");

    const colors = [
        "#eeeeee", // Empty
        "#3498db", // Source
        "#f1c40f", // Mirror
        "#2ecc71", // Goal
    ];

    const drawX = x * CELL_SIZE;
    const drawY = y * CELL_SIZE;

    // マスそのもの
    ctx.fillStyle = colors[tileType];
    ctx.fillRect(drawX, drawY, CELL_SIZE, CELL_SIZE);

    // マスの境界線
    ctx.strokeStyle = "#aaaaaa";
    ctx.strokeRect(drawX, drawY, CELL_SIZE, CELL_SIZE);
});

namespace render {

    void drawTile(GridPosition pos, TileType type) {
        jsDrawTile(pos.x, pos.y, static_cast<int>(type));
    }

} // namespace render
