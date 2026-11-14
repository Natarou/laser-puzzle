#include "Renderer.hpp"
#include <emscripten/emscripten.h>

// C++ から呼び出せる JS 関数を定義
// (戻り値の型, 関数名, 引数)
EM_JS(void, jsDrawTile, (int x, int y, int tileType, int orientation, int CELL_SIZE), {
    // この中は JS
    const canvas = document.getElementById("game");
    const ctx = canvas.getContext("2d");

    // 旧色
    // const colors = [
    //     "#eeeeee", // Empty
    //     "#3498db", // Source
    //     "#f1c40f", // Mirror
    //     "#5c5c5c", // Wall
    //     "#2ecc71", // Goal
    // ];

    // 新色
    const colors = [
        "#17263A", // Empty
        "#2563A6", // Source
        "#E7B85C", // Mirror
        "#35465C", // Wall
        "#31C7A9"  // Goal
    ];

    const drawX = x * CELL_SIZE;
    const drawY = y * CELL_SIZE;

    // マスそのもの
    ctx.fillStyle = colors[tileType];
    ctx.fillRect(drawX, drawY, CELL_SIZE, CELL_SIZE);

    // マスの境界線
    ctx.lineWidth = 1;
    // ctx.strokeStyle = "#aaaaaa"; // 旧色
    ctx.strokeStyle = "#30465F"; // 新色
    ctx.strokeRect(drawX, drawY, CELL_SIZE, CELL_SIZE);

    // 鏡の描画
    if (tileType != 2)
        return;

    let mx1, mx2;
    const my1 = drawY;
    const my2 = drawY + CELL_SIZE;

    if (orientation == 0) { // スラッシュ
        mx1 = drawX + CELL_SIZE;
        mx2 = drawX;
    } else { // バックスラッシュ
        mx1 = drawX;
        mx2 = drawX + CELL_SIZE;
    }

    // ctx.strokeStyle = colors[1]; // 旧色
    ctx.strokeStyle = "#F8E9B6"; // 新色
    ctx.lineWidth = 3;

    // 実際に描く
    ctx.beginPath();
    ctx.moveTo(mx1, my1);
    ctx.lineTo(mx2, my2);
    ctx.stroke();
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
    // ctx.strokeStyle = "#eb4034"; // 旧色
    ctx.strokeStyle = "#FF6475"; // 新色

    // 線を描画
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.stroke();
});

// クリア演出描画
// 旧
// EM_JS(void, jsDrawClearEffect, (int CELL_SIZE), {
//     const canvas = document.getElementById("game");
//     const ctx = canvas.getContext("2d");

//     // 座布団01
//     const two_cell = CELL_SIZE * 2;
//     ctx.fillStyle = "#ffffff8a";
//     ctx.fillRect(0, two_cell, canvas.width, two_cell);

//     // 座布団02
//     ctx.fillStyle = "#f1c40fa0";
//     ctx.fillRect(0, two_cell, canvas.width, two_cell);

//     // 文字
//     ctx.font = "bold 32px sans-serif";
//     ctx.fillStyle = "#2ecc71";
//     ctx.textAlign = "center";
//     ctx.textBaseline = "middle";

//     ctx.fillText("STAGE CLEAR!!", canvas.width / 2, canvas.height / 2);
// });

// クリア演出描画
// 新色
EM_JS(void, jsDrawClearEffect, (int CELL_SIZE), {
    const canvas = document.getElementById("game");
    const ctx = canvas.getContext("2d");

    const panelY = CELL_SIZE * 2;
    const panelHeight = CELL_SIZE * 2;
    const centerX = canvas.width / 2;
    const centerY = canvas.height / 2;

    ctx.save();

    // ① 半透明のダークパネル
    ctx.fillStyle = "rgba(11, 23, 40, 0.6)";
    ctx.fillRect(0, panelY, canvas.width, panelHeight);

    // ② 上下のシアンライン
    ctx.fillStyle = "#60E3D2";
    ctx.fillRect(0, panelY, canvas.width, 2);
    ctx.fillRect(0, panelY + panelHeight - 2, canvas.width, 2);

    // ③ 発光するクリア文字
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.font = "bold 28px sans-serif";

    ctx.shadowColor = "#60E3D2";
    ctx.shadowBlur = 12;
    ctx.fillStyle = "#60E3D2";

    ctx.fillText("STAGE CLEAR!!", centerX, centerY - 9);

    // ④ サブテキスト
    ctx.shadowBlur = 0;
    ctx.font = "10px sans-serif";
    ctx.fillStyle = "#93A6BF";

    ctx.fillText("TARGET REACHED", centerX, centerY + 24);

    ctx.restore();
});


namespace render {

    // タイル（マス）を描画
    void drawTile(GridPosition pos, Tile tile) {
        jsDrawTile(pos.x, pos.y, static_cast<int>(tile.type), static_cast<int>(tile.orientation), CELL_SIZE);
    }

    // 光線を描画
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

    // クリア時演出
    void drawClearEffect() {
        jsDrawClearEffect(CELL_SIZE);
    }

    // JS から受け取ったピクセル座標を GridPosition に変換
    GridPosition convertPixelToGridPos(int pixelX, int pixelY) {
        int gridX = pixelX / CELL_SIZE;
        int gridY = pixelY / CELL_SIZE;
        return GridPosition{gridX, gridY};
    }

} // namespace render
