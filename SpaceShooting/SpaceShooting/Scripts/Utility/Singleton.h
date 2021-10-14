// シングルトン

#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

namespace shooting {
    template<class T>
    class Singleton {
       public:
        Singleton() = default;

        ~Singleton() = default;

       public:
        /// @brief インスタンスを取得 @n なければ作成
        [[nodiscard]] static auto Instance() noexcept -> std::shared_ptr<T>& {
            if ( !instance ) [[unlikely]] {
                instance = std::make_shared<T>();
            }

            return instance;
        }

       private:
        static std::shared_ptr<T> instance;
    };
    template<class T>
    std::shared_ptr<T> Singleton<T>::instance;

}  // namespace shooting

#endif  // !SINGLETON_H
