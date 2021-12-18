
#include <Game/Invoker.hpp>
#include <ranges>

namespace game {
    void Invoker::Regist( std::string_view name, const InvokeData& data ) {
        list.emplace( name, data );
    }

    void Invoker::Unregist( std::string_view name ) noexcept {
        list.erase( name.data() );
    }

    void Invoker::Update() {
        for ( auto&& e : list | std::views::values ) {
            if ( e.Condition() ) {
                e.Method();
            }
        }
    }
}  // namespace game
