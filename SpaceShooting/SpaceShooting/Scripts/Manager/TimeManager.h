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
        /// @brief 初期化
        void Initialize() {
            startTime = GetNowCount();
            fpsStartTime = GetNowCount();
        }

        /// @brief 更新
        void Update() {
            // deltaTime
            int32_t currentTime = GetNowCount();

            // 前回の処理にかかった時間
            deltaTime = ToSeconds( currentTime - startTime );
            startTime = currentTime;

            // deltaTimeが大きすぎる場合は不具合を回避するためdeltaTimeを0に
            if ( deltaTime >= TIME_SKIP ) {
                deltaTime = 0.0f;
                printfDx( "FPS : %d\n", fps );
            }

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
        ReadonlyProperty<float> DeltaTime { deltaTime };

        /// @brief 1秒あたりの処理回数
        ReadonlyProperty<int32_t> FPS { fps };

       private:
        static constexpr float TIME_SKIP { 0.2f };  // deltaTimeはこの値を超えた場合0を返す

        static constexpr int32_t MS_CONVERT_SOURCE { 1000 };
        static constexpr float S_CONVERT_SOURCE { 1000.0f };

        int32_t startTime { 0 };  // deltaTime計測開始時間
        float deltaTime { 0.0f };  // 前回の処理にかかった時間

        int32_t fpsStartTime { 0 };  // fps計測開始時間
        int32_t fpsCount { 0 };  // 計測開始からの処理回数を記録
        int32_t fps { 0 };  // 1秒あたりの処理回数
    };
}  // namespace shooting

#endif  // !TIME_MANAGER_H
