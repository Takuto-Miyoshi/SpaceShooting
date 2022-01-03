
// オブジェクトの情報

#ifndef OBJECT_DATA_HPP
#define OBJECT_DATA_HPP

#include <string>

namespace game {
    struct ObjectData {
        bool IsActive { false };  // アクティブなオブジェクトか

        std::string TexturePath { "" };  // テクスチャのファイルパス
        std::string TextureName { "" };  // テクスチャの登録名
    };
}  // namespace game

#endif  // !OBJECT_DATA_HPP
