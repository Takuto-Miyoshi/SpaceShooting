// deltaTime依存のタイマー

#ifndef TIMER_H
#define TIMER_H

#include <functional>

#include "Property.hpp"

namespace shooting {
    class Timer {
       public:
        /// @brief 自動処理タイマー
        /// @param interval_ 処理を呼び出す間隔
        /// @param func_ 実行する処理
        /// @param loop_ 処理が呼び出された時に繰り返すかどうか
        explicit Timer( double& interval_, std::function<void()>&& func_, bool&& loop_ = true ) noexcept;

        ~Timer() noexcept;

       public:
        _declspec( noinline ) void Update();

       public:
        ReadonlyProperty<bool> End { end };

       private:
        double& interval;
        double timer { 0.0 };
        bool loop { false };  // タイマーを繰り返すか
        std::function<void()> func {};  // 実行する処理

        bool end { false };  // 処理終了フラグ
    };
}  // namespace shooting

#endif  // !TIMER_H
