// 画像に関する定義

#ifndef IMAGE_DEFINITION_H
#define IMAGE_DEFINITION_H

#include <cstdint>
#include <string>

namespace shooting::image {
    struct ImageData {
        std::string filePath;  // 画像のパス
        std::string name;  // 画像の登録名
    };

    constexpr uint32_t DATA_CAPACITY { 3 };

    const ImageData PLAYER { "Images/Object/Actor/Player.png", "Player" };

    const ImageData STANDARD_ENEMY { "Images/Object/Actor/StandardEnemy.png", "StandardEnemy" };
    const ImageData EXPLODE_ENEMY { "Images/Object/Actor/ExplodeEnemy.png", "ExplodeEnemy" };

    const ImageData STANDARD_BULLET { "Images/Object/Bullet/StandardBullet.png", "StandardBullet" };
}  // namespace shooting::image

#endif  // !IMAGE_DEFINITION_H
