// 時間を記録

#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <cstdint>

#include "../Utility/Property.h"
#include "../Utility/Singleton.h"
#include "DxLib.h"

namespace shooting {
    class TimeManager : public Singleton<TimeManager> {
       public:
        TimeManager() = default;

        ~TimeManager() = default;

       public:
        void Initialize() {
            startTime = GetNowCount();
            fpsStartTime = GetNowCount();
        }

        void Update() {
            // deltaTime
            int32_t currentTime = GetNowCount();

            // 前回の処理にかかった時間
            deltaTime = ToSeconds( currentTime - startTime );
            startTime = currentTime;

            // fps
            fpsCount++;

            if ( currentTime >= ( fpsStartTime + ToMilliseconds( 1 ) ) ) {
                // 計測から1秒経過時点でのカウント=FPS
                fps = fpsCount;
                fpsCount = 0;
                fpsStartTime = currentTime;
            }
        }

       public:
        /// @brief 秒をミリ秒に変換
        [[nodiscard]] static constexpr auto ToMilliseconds( int32_t seconds ) -> int32_t { return seconds * MS_CONVERT_SOURCE; }

        /// @brief ミリ秒を秒に変換
        [[nodiscard]] static constexpr auto ToSeconds( int32_t milliseconds ) -> float { return milliseconds / S_CONVERT_SOURCE; }

       public:
        /// @brief 前回の処理にかかった時間(s)
        Property<float> DeltaTime { deltaTime };

        /// @brief 1秒あたりの処理回数
        Property<int32_t> FPS { fps };

       private:
        static constexpr int32_t MS_CONVERT_SOURCE = 1000;
        static constexpr float S_CONVERT_SOURCE = 1000.0f;

        int32_t startTime { 0 };  // deltaTime計測開始時間
        float deltaTime { 0.0f };  // 前回の処理にかかった時間

        int32_t fpsStartTime { 0 };  // fps計測開始時間
        int32_t fpsCount { 0 };  // 計測開始からの処理回数を記録
        int32_t fps { 0 };  // 1秒あたりの処理回数
    };
}  // namespace shooting

#endif  // !TIME_MANAGER_H
