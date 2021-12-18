
#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP

#include <Game/Structures.hpp>
#include <string>

namespace game {
    class GameLoop {
       public:
        /// @brief 初期設定用
        struct DxLibConfig {
            Size<int32_t> ScreenSize {};
            int32_t ColorBitDepth {};
            int32_t FrameRate {};
            bool EnableFullscreen {};
            std::string WindowName { "" };
            bool EnableVSync {};
        };

       public:
        GameLoop( const DxLibConfig& config );

        ~GameLoop();

       public:
        /// @brief ゲームループを実行
        void Exec();

       private:
        /// @brief DxLib初期設定
        void DxInitialize( const DxLibConfig& config );

        /// @brief DxLib終了処理
        void DxFinalize();

       private:
        /// @brief 失敗
        /// @note DxLib用
        static constexpr auto FAIL { -1 };

        int32_t targetFPS {};
    };
}  // namespace game

#endif  // !GAME_LOOP_HPP
