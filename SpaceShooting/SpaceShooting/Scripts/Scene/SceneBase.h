// シーンの基底クラス

#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "../Definition/SceneDefinition.h"
#include "../Utility/Property.h"

namespace shooting::scene {
    class SceneBase {
       public:
        SceneBase() = default;

        virtual ~SceneBase() = default;

       public:
        /// @brief シーンが作成された後一度だけ実行
        virtual void Start() = 0;

        /// @brief 毎フレーム実行（計算）
        virtual void Update() = 0;

        /// @brief 毎フレーム実行（描画）
        virtual void Draw() = 0;

        /// @brief 終了時に一度だけ実行
        virtual void Finalize() = 0;

       protected:
        /// @brief シーンを変更する
        /// @param next 遷移先のシーン
        constexpr void ChangeScene( const SceneDefs& next ) {
            change = true;
            nextScene = next;
        }

       public:
        /// @brief ゲームを終了するか
        Property<bool> EndGame { endGame };

        /// @brief シーンを変更するか
        ReadonlyProperty<bool> Change { change };

        /// @brief 遷移先のシーン
        ReadonlyProperty<SceneDefs> NextScene { nextScene };

       private:
        bool endGame { false };  // ゲームを終了するか

        bool change { false };  // シーンを変更するか
        SceneDefs nextScene { SceneDefs::Title };  // 遷移先のシーン
    };
}  // namespace shooting::scene

#endif  // !SCENE_BASE_H
