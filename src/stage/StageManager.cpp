#include "StageManager.hpp"
#include <cassert>
#include <set>

// clang-format off
StageManager::StageManager()
    : stages_{
        {
            StageId::Tutorial, Stage{
                {{0, 0}, {TileType::Source}},
                {{3, 0}, {TileType::Mirror}},
                {{3, 5}, {TileType::Goal}},
            }
        },
        {
            StageId::Reflection, Stage{
                {{0, 0}, {TileType::Source}},
                {{5, 0}, {TileType::Mirror}},
                {{5, 5}, {TileType::Mirror, MirrorOrientation::BackSlash}},
                {{0, 5}, {TileType::Goal}},
            }
        },
        {
            StageId::Wall, Stage{
                {{0, 0}, {TileType::Source}},
                {{5, 0}, {TileType::Mirror}},
                {{5, 3}, {TileType::Mirror, MirrorOrientation::BackSlash}},
                {{2, 3}, {TileType::Mirror, MirrorOrientation::BackSlash}},
                {{2, 4}, {TileType::Mirror, MirrorOrientation::BackSlash}},
                {{0, 4}, {TileType::Mirror, MirrorOrientation::BackSlash}},
                {{0, 1}, {TileType::Mirror}},
                {{4, 1}, {TileType::Mirror}},
                {{4, 2}, {TileType::Mirror}},
                {{0, 5}, {TileType::Goal}},
            }
        },
    },
    stageOrder_{
        StageId::Tutorial,
        StageId::Reflection,
        StageId::Wall,
    }
{
    // 定義されたステージが正常かチェック
    assert(!stageOrder_.empty());

    // 同じ ID が 2 回登録されてないか確認
    std::set<StageId> registeredIds;

    for (const StageId id : stageOrder_) {
        assert(findStage(id) != nullptr);
        // 登録できたら second に true が入っているはず
        const bool inserted = registeredIds.insert(id).second; // 副作用がある処理は assert の中に書かない
        assert(inserted);
    }

    // 辞書の全ステージが順序に含まれるか確認
    assert(registeredIds.size() == stages_.size());

    // 各ステージの配置が正しいか確認
    for (const auto& [id, stage] : stages_) {
        assert(stage.isValid());
    }
}
// clang-format on

// ステージの取得
// 見つからなかった時に nullptr を返すためポインタを返すようにしてる
const Stage* StageManager::findStage(StageId stageId) const {
    // C++ は存在しないキーを指定すると、新しい要素が自動的に追加されるので、より安全に取得する
    // イテレータ取得
    auto it = stages_.find(stageId);

    // イテレータが末尾の無を指し示してたら無
    // キーが存在しなかったら
    if (it == stages_.end())
    {
        return nullptr; // ぬるぽ
    }

    // 対応する値を返す
    return &it->second; // first だと key の方を返す
}

// 次のステージを取得する
StageId StageManager::getNextStageId(StageId currentStageId) const {
    // size() の戻り値が size_t なので仕方なく size_t を使用している
    for (std::size_t i = 0; i < stageOrder_.size(); i++) {
        std::size_t nextIdx = (i + 1) % stageOrder_.size();
        return stageOrder_[nextIdx];
    }

    return stageOrder_.front();
}
