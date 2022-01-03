
// ゲームオブジェクトの基底クラス

#ifndef OBJECT_BASE_HPP
#define OBJECT_BASE_HPP

#include <Game/Object/Component/Renderer.hpp>
#include <Game/Object/ObjectData.hpp>

namespace game {
    class ObjectBase {
       public:
        ObjectBase() = default;

        virtual ~ObjectBase() = default;

       public:
        void Initialize();

        void Exec();

        void Draw() const;

       protected:
        /// @brief 初期パラメータを設定する
        virtual void SetDefault() = 0;

       protected:
        ObjectData object {};

        component::Transform transform {};
        component::Renderer renderer {};
    };
}  // namespace game

#endif  // !OBJECT_BASE_HPP
