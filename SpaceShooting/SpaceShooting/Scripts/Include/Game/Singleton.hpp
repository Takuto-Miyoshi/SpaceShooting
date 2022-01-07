
// シングルトン

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <memory>

namespace game {
    template<typename T>
    class Singleton {
       public:
        using type = T;

       public:
        Singleton() = default;

        virtual ~Singleton() = default;

       public:
        [[nodiscard]] static constexpr auto Instance() -> const std::shared_ptr<T>& {
            if ( !instance ) [[unlikely]] {
                instance = std::make_shared<T>();
            }

            return instance;
        }

       private:
        static std::shared_ptr<type> instance;
    };
    template<typename T>
    std::shared_ptr<T> Singleton<T>::instance;
}  // namespace game

#endif  // !SINGLETON_HPP
