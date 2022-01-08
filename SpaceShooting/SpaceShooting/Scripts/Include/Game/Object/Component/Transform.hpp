
// 位置や角度の情報

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <Game/Vector.hpp>

namespace game::component {
    class Transform {
       public:
        Transform() = default;

        ~Transform() = default;

       public:
        /// @brief 位置情報
        Accessor<Vector2> Position { position };

        /// @brief ベクトル角
        Accessor<Vector2> Direction { direction };

        /// @brief ラジアン角
        template<std::floating_point T = float>
        [[nodiscard]] auto Angle() const& noexcept -> T {
            return Vector2::ToAngle( direction );
        }

       private:
        Vector2 position {};
        Vector2 direction {};
    };
}  // namespace game::component

#endif  // !TRANSFORM_HPP
