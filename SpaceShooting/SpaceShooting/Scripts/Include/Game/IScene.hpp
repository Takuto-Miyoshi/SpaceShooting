
// シーンのインターフェース

#ifndef ISCENE_HPP
#define ISCENE_HPP

namespace game {
    class IScene {
       public:
        IScene() = default;

        virtual ~IScene() = default;

       public:
        /// @brief シーンが変更されたときに行う処理
        virtual void Initialize() = 0;

        /// @brief 処理
        virtual void Update() = 0;

        /// @brief 描画
        virtual void Draw() = 0;

        /// @brief シーンを変更するときに行う処理
        virtual void Finalize() = 0;
    };
}  // namespace game

#endif  // !ISCENE_HPP
