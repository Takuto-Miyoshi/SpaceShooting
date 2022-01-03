
// テクスチャの管理

#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <Game/Singleton.hpp>
#include <map>
#include <string>

namespace game {
    class TextureManager : public Singleton<TextureManager> {
       public:
        TextureManager() = default;

        ~TextureManager() override = default;

       public:
        /// @brief 画像を読み込む
        /// @param name 登録名
        /// @param file 画像のパス
        void Load( std::string_view name, std::string_view file );

        /// @brief 画像を取得
        /// @param name 取得する画像の登録名
        auto Get( std::string_view name ) const -> int32_t;

        /// @brief 読み込んだ画像を全て解放
        void Release() noexcept;

        /// @brief 読み込んだ画像を解放
        /// @param name 解放する画像の登録名
        void Release( std::string_view name ) noexcept;

       private:
        static constexpr int8_t DX_ERROR { -1 };

        std::map<std::string, int32_t> textureList {};
    };
}  // namespace game

#endif  // !TEXTURE_MANAGER_HPP
