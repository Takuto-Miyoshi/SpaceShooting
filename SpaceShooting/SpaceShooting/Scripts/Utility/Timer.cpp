#include "Timer.h"

#include "../Manager/TimeManager.h"

namespace shooting {
    Timer::Timer( double& interval_, std::function<void()>&& func_, bool&& loop_ ) noexcept :
        interval( interval_ ), func( std::move( func_ ) ), loop( std::move( loop_ ) ) {
        timer = interval;
        TimeManager::Instance()->Regist( this );
    }

    Timer::~Timer() noexcept {
        end = true;
    }

    _declspec( noinline ) void Timer::Update() {
        if ( end ) { return; }

        timer -= TimeManager::Instance()->DeltaTime;

        if ( timer <= 0 ) {
            func();
            timer = interval;

            if ( !loop ) { end = true; }
        }
    }
}  // namespace shooting
