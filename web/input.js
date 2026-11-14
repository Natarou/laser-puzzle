const canvas = document.getElementById("game");

// 鏡をクリックして回す
canvas.addEventListener("click", (event) => {
    // canvas がどこに表示されていて、どんな大きさなのか取得
    // rect.left : 画面左端から canvas 左端までの距離
    // rect.width : 画面上に表示されている canvas の横幅
    const rect = canvas.getBoundingClientRect();

    // css 上の座標 -> Canvas 内部のピクセル座標
    // event.clientX : クリックしたx 座標
    //.  canvas.width / rect.width : canvas 解像度ヨコ / 実際のヨコ = ヨコ比率
    const x = (event.clientX - rect.left) * canvas.width / rect.width;
    const y = (event.clientY - rect.top) * canvas.height / rect.height;

    // ピクセル座標をそのまま C++ に渡す
    Module._handleClick(x, y);
});

// リスタートボタン
document.getElementById("restart-button").addEventListener("click", () => {
    Module._restartGame();
});

// 次のステージへ進む
document.getElementById("next-stage-button").addEventListener("click", () => {
    Module._gotoNextStage();
});
