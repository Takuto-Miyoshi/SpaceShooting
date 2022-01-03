
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
        BasicProperty<Vector2<double>> Position { position };

        /// @brief ベクトル角
        BasicProperty<Vector2<double>> Direction { direction };

        /// @brief ラジアン角
        template<std::floating_point T = float>
        [[nodiscard]] auto Angle() const& noexcept -> T {
            return Vector2<T>::ToAngle( direction );
        }

       private:
        Vector2<double> position {};
        Vector2<double> direction {};
    };
}  // namespace game::component

#endif  // !TRANSFORM_HPP
