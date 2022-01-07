
#include <Game/InputInvoker.hpp>
#include <Game/InputManager.hpp>
#include <ranges>

namespace game {
    void InputInvoker::Regist( std::string_view name, const InvokeData& data ) {
        list.emplace( name, data );
    }

    void InputInvoker::Regist( std::string_view name, const InvokeSpec& data ) {
        listSpec.emplace( name, data );
    }

    void InputInvoker::Unregist( std::string_view name ) noexcept {
        list.erase( name.data() );
        listSpec.erase( name.data() );
    }

    void InputInvoker::Update() {
        for ( auto&& e : list | std::views::values ) {
            if ( auto& state { InputManager::Instance()->KeyState( e.KeyId ) };
                 state != InputState::None ) {
                e.Method( state );
            }
        }

        for ( auto&& e : listSpec | std::views::values ) {
            if ( auto& state { InputManager::Instance()->KeyState( e.KeyId ) };
                 state == e.State ) {
                e.Method();
            }
        }
    }
}  // namespace game
