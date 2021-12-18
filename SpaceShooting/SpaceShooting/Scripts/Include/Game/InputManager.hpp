
// 入力状態の更新

#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <Game/Enums.hpp>
#include <Game/Singleton.hpp>
#include <Game/Vector.hpp>
#include <array>

namespace game {
    constexpr uint8_t MOUSEBUTTON_LEFT { 0 };
    constexpr uint8_t MOUSEBUTTON_RIGHT { 1 };
    constexpr uint8_t MOUSEBUTTON_MIDDLE { 2 };

    class InputManager : public Singleton<InputManager> {
       public:
        using cursor_position_type = Vector2<double>;

       public:
        InputManager();

        ~InputManager() override = default;

       public:
        void Update() & noexcept;

        [[nodiscard]] constexpr auto KeyState( const int32_t& id ) & noexcept -> const InputState& {
            try {
                return keyList.at( id );
            }
            catch ( const std::exception& ) {
                return *keyList.begin();
            }
        }

        [[nodiscard]] constexpr auto MousebuttonState( const int32_t& id ) & noexcept -> const InputState& {
            try {
                return mousebuttonList.at( id );
            }
            catch ( const std::exception& ) {
                return *mousebuttonList.begin();
            }
        }

        Accessor<cursor_position_type>::Get CursorPosition { cursorPosition };

       private:
        [[nodiscard]] static constexpr auto ConvertState( const InputState& previous, const bool& current ) noexcept -> InputState;

        constexpr void UpdateKeyState() noexcept;

        constexpr void UpdateMousebutton() noexcept;

        void UpdateCursorPosition() noexcept;

       private:
        static constexpr uint16_t NUMBER_OF_KEY { 256 };
        static constexpr uint8_t NUMBER_OF_MOUSEBUTTON { 3 };

        static constexpr int8_t DX_PRESSED { 1 };
        static constexpr uint8_t DX_NOT_PRESSED { 0 };

        std::array<InputState, NUMBER_OF_KEY> keyList {};
        std::array<InputState, NUMBER_OF_MOUSEBUTTON> mousebuttonList {};
        cursor_position_type cursorPosition {};
    };
}  // namespace game

#endif  // !INPUT_MANAGER_HPP
