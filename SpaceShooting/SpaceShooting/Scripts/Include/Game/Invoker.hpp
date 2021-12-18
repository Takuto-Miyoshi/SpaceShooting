
// 条件による関数呼び出し

#ifndef INVOKER_HPP
#define INVOKER_HPP

#include <Game/Singleton.hpp>
#include <functional>
#include <map>

namespace game {
    class Invoker : public Singleton<Invoker> {
       public:
        struct InvokeData {
            std::function<bool()> Condition;  // 条件式
            std::function<void()> Method;  // 実行する関数
        };

       public:
        Invoker() = default;

        ~Invoker() override = default;

       public:
        /// @brief 関数を登録
        /// @param name 登録名
        /// @param data 関数データ
        void Regist( std::string_view name, const InvokeData& data );

        /// @brief 登録したデータを削除
        /// @param name 登録名
        void Unregist( std::string_view name ) noexcept;

        /// @brief 更新
        void Update();

       private:
        std::multimap<std::string, InvokeData> list {};
    };
}  // namespace game

#endif  // !INVOKER_HPP
