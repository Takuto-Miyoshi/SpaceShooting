// 時間を管理

#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

#include "../Utility/Property.h"
#include "../Utility/Singleton.h"
#include "../Utility/Timer.h"

namespace shooting {
    class TimeManager : public Singleton<TimeManager> {
       public:
        TimeManager() = default;

        ~TimeManager() = default;

       public:
        /// @brief 初期化
        void Initialize() noexcept;

        /// @brief 更新
        void Update() noexcept;

        /// @brief タイマーを登録
        void Regist( const Timer* timer );

        /// @brief タイマーリストをリセット
        void ResetTimerList() noexcept;

       private:
        void UpdateDeltaTime() noexcept;

        void UpdateFPS() noexcept;

        void UpdateTimer();

       public:
        /// @brief 秒をミリ秒に変換
        [[nodiscard]] static constexpr auto ToMilliseconds( const std::integral auto& seconds ) noexcept -> int32_t { return seconds * MS_CONVERT_SOURCE; }

        /// @brief ミリ秒を秒に変換
        [[nodiscard]] static constexpr auto ToSeconds( const std::integral auto& milliseconds ) noexcept -> double { return milliseconds / S_CONVERT_SOURCE; }

       private:
        [[nodiscard]] constexpr auto Now() const noexcept -> int64_t;

       public:
        /// @brief 前回の処理にかかった時間(s)
        ReadonlyProperty<double> DeltaTime { deltaTime };

        /// @brief 1秒あたりの処理回数
        ReadonlyProperty<int32_t> FPS { fps };

       private:
        static constexpr double TIME_SKIP { 0.2 };  // deltaTimeの上限 バグ防止

        static constexpr int32_t MS_CONVERT_SOURCE { 1000 };
        static constexpr double S_CONVERT_SOURCE { 1000.0 };

        int64_t startTime { 0 };  // deltaTime計測開始時間
        double deltaTime { 0.0 };  // 前回の処理にかかった時間

        int64_t fpsStartTime { 0 };  // fps計測開始時間
        int32_t fpsCount { 0 };  // 計測開始からの処理回数を記録
        int32_t fps { 0 };  // 1秒あたりの処理回数

        static constexpr uint32_t TIMER_LIST_CAPACITY { 200 };
        std::vector<std::shared_ptr<Timer>> timerList {};  // 処理するタイマーのリスト
    };
}  // namespace shooting

#endif  // !TIME_MANAGER_H
