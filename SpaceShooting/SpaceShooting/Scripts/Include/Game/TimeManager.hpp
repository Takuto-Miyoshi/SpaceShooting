
// 時間管理

#ifndef TIME_MANAGER_HPP
#define TIME_MANAGER_HPP

#include <Game/Concepts.hpp>
#include <Game/Property.hpp>
#include <Game/Singleton.hpp>

namespace game {
    class TimeManager : public Singleton<TimeManager> {
       public:
        TimeManager() = default;

        ~TimeManager() override = default;

       public:
        /// @brief 更新
        void Update() noexcept;

        /// @brief フレームレートを目標値に調整する
        void MarkFPS( const int32_t& targetFPS );

       private:
        /// @brief 前回のフレームにかかった時間を更新
        void UpdateDeltaTime() noexcept;

        /// @brief フレームレートを更新
        void UpdateFPS() noexcept;

        /// @brief 今の時間を取得
        static auto Now() noexcept -> int64_t;

       public:
        /// @brief フレームレート
        ReadonlyProperty<int32_t> FPS { fps };

        /// @brief 前回のフレームにかかった時間
        ReadonlyProperty<double> DeltaTime { deltaTime };

       private:
        template<concepts::numeric T>
        static constexpr T MILLI_SECONDS { static_cast<T>( 1000.0 ) };

        int64_t deltaTimeRap { Now() };
        double deltaTime {};

        int64_t fpsRap { Now() };
        int32_t fps {};
        int32_t fpsCount {};
    };
}  // namespace game

#endif  // !TIME_MANAGER_HPP
