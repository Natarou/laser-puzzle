#include "Laser.hpp"

// 経路をまとめて計算
LaserResult Laser::trace(const Board &board) {
    // 光源の位置へ戻す
    // TODO: 光源のクラスを作ったらそこから座標を取るようにする
    state_ = LaserState{GridPosition{0, 0}, Direction::Right};

    // 状態記録
    // visited[y][x][direction]
    bool visited[Board::SIZE][Board::SIZE][4] = {};
    visited[state_.position.y][state_.position.x][static_cast<int>(state_.direction)] = true;

    // 座標記録
    path_.clear();
    path_.push_back(state_.position); // スタート地点を記録
    LaserResult currentLaserResult = LaserResult::Movable;

    // 動ける && 状態が被らない限り進む
    while (currentLaserResult == LaserResult::Movable) {
        currentLaserResult = step(board);

        // currentLaserResult を不必要に書き換えないよう止める
        if (currentLaserResult != LaserResult::Movable)
            break;

        // 無限ループ対策
        int currentY = state_.position.y;
        int currentX = state_.position.x;
        int currentD = static_cast<int>(state_.direction);

        // ループしてた場合
        if (visited[currentY][currentX][currentD]) {
            currentLaserResult = LaserResult::LoopDetected;
            break;
        }

        visited[currentY][currentX][currentD] = true;
    }

    return currentLaserResult;
}

// 1 マスずつ数む
LaserResult Laser::step(const Board &board) {
    GridPosition nextPos = calcNextPos();

    if (!board.isInsideGrid(nextPos))
        return LaserResult::OutOfGrid; // 範囲外ならここで終わり

    // 進んだ先のタイルを取得
    Tile tile = board.getTile(nextPos);
    TileType type = tile.type;

    if (type == TileType::Wall)
        return LaserResult::HitWall;

    // 次の座標に移動
    state_.position = nextPos;

    // 座標記録
    path_.push_back(state_.position);

    // 進んだ先のタイルの種類によって状態変わる
    if (type == TileType::Mirror) // 鏡
    {
        reflect(tile.orientation);     // 進行方向を変える
    } else if (type == TileType::Goal) // ゴール
    {
        // ゴールしたらここで終わり
        return LaserResult::ReachedGoal;
    }

    return LaserResult::Movable;
}

// 次の座標を計算
GridPosition Laser::calcNextPos() const {
    int currentDNum = static_cast<int>(state_.direction);

    GridPosition step = GridPosition{0, 0};
    if (currentDNum % 2 == 0) {
        // 上下
        step.y = 1 * (currentDNum - 1); // U : -1, D : 1 になる
    } else {
        // 左右
        step.x = 1 * (currentDNum - 2); // L : -1, R : 1 になる
    }

    return GridPosition{state_.position.x + step.x, state_.position.y + step.y};
}

// 鏡の反射
void Laser::reflect(MirrorOrientation orientation) {
    Direction currentStateD = state_.direction;
    Direction nextStateD = Direction::Up;
    if (orientation == MirrorOrientation::Slash) { // スラッシュ
        switch (currentStateD) {
        case Direction::Up:
            nextStateD = Direction::Right;
            break;
        case Direction::Left:
            nextStateD = Direction::Down;
            break;
        case Direction::Down:
            nextStateD = Direction::Left;
            break;
        case Direction::Right:
            nextStateD = Direction::Up;
            break;
        }
    } else { // バックスラッシュ
        switch (currentStateD) {
        case Direction::Up:
            nextStateD = Direction::Left;
            break;
        case Direction::Left:
            nextStateD = Direction::Up;
            break;
        case Direction::Down:
            nextStateD = Direction::Right;
            break;
        case Direction::Right:
            nextStateD = Direction::Down;
            break;
        }
    }
    state_.direction = nextStateD;
}

// 経路を返す
const std::vector<GridPosition> &Laser::getPath() const {
    return path_;
}
