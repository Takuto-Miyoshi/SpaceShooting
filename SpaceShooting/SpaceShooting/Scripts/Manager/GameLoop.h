// ゲームのメインループ

#ifndef GAME_LOOP_H
#define GAME_LOOP_H

namespace shooting {
    class GameLoop {
       public:
        GameLoop() = default;

        ~GameLoop() = default;

       public:
        /// @brief メインループを実行
        void Exec();
    };
}  // namespace shooting

#endif  // !GAME_LOOP_H
