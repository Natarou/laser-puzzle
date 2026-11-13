#include <emscripten/emscripten.h>
#include "Board.hpp"

// C++ から呼び出せる JS 関数を定義
// (戻り値の型, 関数名, 引数)
EM_JS(void, drawRect, (int x, int y, int tileType), {
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


int main () {
    Board board;

    // Game::initialize() に移植
    // board.setTile(GridPosition{0, 0}, Tile{TileType::Source});
    // board.setTile(GridPosition{3, 2}, Tile{TileType::Mirror});
    // board.setTile(GridPosition{3, 5}, Tile{TileType::Goal});

    // Game::render() に移植
    // 盤面を描画
    // for (int y = 0; y < Board::SIZE; y++) {
    //     for (int x = 0; x < Board::SIZE; x++) {
    //         Tile tile = board.getTile(GridPosition{x, y});
    //         drawRect(x, y, static_cast<int>(tile.type));
    //     }
    // }

    return 0;
}
