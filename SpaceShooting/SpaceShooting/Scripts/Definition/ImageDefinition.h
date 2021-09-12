// 画像に関する定義

#ifndef IMAGE_DEFINITION_H
#define IMAGE_DEFINITION_H

#include <string>

namespace shooting::image {
    struct ImageData {
        std::string filePath;  // 画像のパス
        std::string name;  // 画像の登録名
    };

    const ImageData player { "Images/Object/Actor/Player.png", "Player" };

    const ImageData enemy { "Images/Object/Actor/Enemy.png", "Enemy" };

    const ImageData standardBullet { "Images/Object/Bullet/StandardBullet.png", "StandardBullet" };
}  // namespace shooting::image

#endif  // !IMAGE_DEFINITION_H
