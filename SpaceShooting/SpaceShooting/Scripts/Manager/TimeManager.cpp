#include "TimeManager.h"

#include <chrono>

#include "DxLib.h"

namespace shooting {
    void TimeManager::Initialize() noexcept {
        startTime = Now();
        fpsStartTime = Now();

        timerList.reserve( TIMER_LIST_CAPACITY );
    }

    void TimeManager::Update() noexcept {
        UpdateDeltaTime();
        UpdateFPS();
        UpdateTimer();
    }

    void TimeManager::Regist( const Timer* timer ) {
        timerList.push_back( std::make_shared<Timer>( *timer ) );
    }

    void TimeManager::ResetTimerList() noexcept {
        timerList.clear();
    }

    void TimeManager::UpdateDeltaTime() noexcept {
        const auto now { Now() };

        // 前回の処理にかかった時間
        deltaTime = ToSeconds( now - startTime );
        startTime = now;

        // deltaTimeが大きすぎる場合は不具合を回避するためdeltaTimeを上限値に
        if ( deltaTime >= TIME_SKIP ) [[unlikely]] {
            deltaTime = TIME_SKIP;
            printfDx( "FPS : %d\n", fps );
        }
    }

    void TimeManager::UpdateFPS() noexcept {
        fpsCount++;

        if ( const auto now { Now() }; now >= ( fpsStartTime + ToMilliseconds( 1 ) ) ) [[unlikely]] {
            // 計測から1秒経過時点でのカウント=FPS
            fps = fpsCount;
            fpsCount = 0;
            fpsStartTime = now;
        }
    }

    void TimeManager::UpdateTimer() {
        std::erase_if( timerList, []( const auto& element ) { return element->End; } );

        for ( auto&& element : timerList ) {
            element->Update();
        }
    }

    constexpr auto TimeManager::Now() const noexcept -> int64_t {
        return std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch() ).count();
    }
}  // namespace shooting
