#include "Renderer.hpp"
#include <emscripten/emscripten.h>

// C++ から呼び出せる JS 関数を定義
// (戻り値の型, 関数名, 引数)
EM_JS(void, jsDrawTile, (int x, int y, int tileType, int CELL_SIZE), {
    // この中は JS
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

// Laser 描画
EM_JS(void, jsDrawLaser, (int startX, int startY, int destinationX, int destinationY, int CELL_SIZE), {
    // この中は JS
    const canvas = document.getElementById("game");
    const ctx = canvas.getContext("2d");

    // ここ関数化できないかな
    const x1 = startX * CELL_SIZE + CELL_SIZE / 2;
    const y1 = startY * CELL_SIZE + CELL_SIZE / 2;
    const x2 = destinationX * CELL_SIZE + CELL_SIZE / 2;
    const y2 = destinationY * CELL_SIZE + CELL_SIZE / 2;

    // 線のスタイル
    ctx.lineWidth = 5;
    ctx.strokeStyle = "#eb4034";

    // 線を描画
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.stroke();
});

namespace render {

    void drawTile(GridPosition pos, TileType type) {
        jsDrawTile(pos.x, pos.y, static_cast<int>(type), CELL_SIZE);
    }

    void drawLaser(const std::vector<GridPosition> &path) {
        if (path.size() < 2)
            return;

        GridPosition currentPos = path.front();
        bool isFirst = true;
        for (const GridPosition &val : path) {
            // 最初の要素なら飛ばす
            if (isFirst) {
                isFirst = false;
                continue;
            }

            jsDrawLaser(currentPos.x, currentPos.y, val.x, val.y, CELL_SIZE);
            currentPos = val;
        }
    }

    GridPosition convertPixelToGridPos(int pixelX, int pixelY) {
        int gridX = pixelX / CELL_SIZE;
        int gridY = pixelY / CELL_SIZE;
        return GridPosition{gridX, gridY};
    }

} // namespace render
