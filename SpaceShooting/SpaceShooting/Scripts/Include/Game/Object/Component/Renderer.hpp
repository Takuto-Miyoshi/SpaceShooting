
// 画像の表示

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <Game/Object/Component/Transform.hpp>

namespace game::component {
    class Renderer {
       public:
        Renderer() = default;

        ~Renderer() = default;

       public:
        /// @brief 読み込んだ画像をキャッシュに保存する
        /// @param name 画像の登録名
        void Load( std::string_view name );

        /// @brief 画像を読み込んでキャッシュに保存する
        /// @param name 画像の登録名
        /// @param file 画像のファイルパス
        void Load( std::string_view name, std::string_view file );

        /// @brief キャッシュの画像を表示する
        /// @param transform 表示のための情報
        void Draw( const Transform& transform ) const;

       private:
        int32_t handle {};
    };
}  // namespace game::component

#endif  // !RENDERER_HPP
