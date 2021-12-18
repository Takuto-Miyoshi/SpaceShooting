
#include <DxLib.h>

#include <Game/TimeManager.hpp>
#include <chrono>

using namespace std::chrono_literals;

namespace game {
    void TimeManager::Update() noexcept {
        UpdateDeltaTime();
        UpdateFPS();
    }

    void TimeManager::MarkFPS( const int32_t& targetFPS ) {
        const auto frameTime { MILLI_SECONDS<int32_t> / targetFPS };  // 1フレームにかけるべき時間(ms)
        const auto processTime { Now() - deltaTimeRap };  // ここまでの処理時間(ms)
        const auto waitTime { frameTime - processTime };  // 待つべき時間(ms)
        WaitTimer( static_cast<int32_t>( waitTime ) );
    }

    void TimeManager::UpdateDeltaTime() noexcept {
        const auto now { Now() };
        deltaTime = static_cast<double>( now - deltaTimeRap ) / MILLI_SECONDS<double>;
        deltaTimeRap = now;
    }

    void TimeManager::UpdateFPS() noexcept {
        ++fpsCount;

        if ( const auto now { Now() };
             now >= fpsRap + MILLI_SECONDS<int32_t> ) {
            fps = fpsCount;
            fpsCount = 0;
            fpsRap = now;
        }
    }

    auto TimeManager::Now() noexcept -> int64_t {
        return std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch() ).count();
    }
}  // namespace game
