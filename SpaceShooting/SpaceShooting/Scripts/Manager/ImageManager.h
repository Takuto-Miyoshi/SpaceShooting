// 画像を管理

#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include "../Definition/ImageDefinition.h"
#include "../Utility/Singleton.h"
#include "DxLib.h"

namespace shooting {
    class ImageManager : public Singleton<ImageManager> {
       private:
        struct RegistImageData {
            int32_t graphicHandle;  // 画像のハンドル
            std::string name;  // 登録名
        };

       public:
        ImageManager() = default;

        ~ImageManager() = default;

       public:
        /// @brief 初期化
        void Initialize() {
            imageDataList.reserve( image::DATA_CAPACITY );
        }

        /// @brief 読み込んだ画像を取得
        /// @param name 登録名
        [[nodiscard]] auto Image( const std::string& name ) const -> int32_t {
            auto result = std::find_if( imageDataList.begin(), imageDataList.end(), [&name]( auto element ) {
                return element.name == name;
            } );

            if ( result == imageDataList.end() ) { return -1; }

            return result->graphicHandle;
        }

        /// @brief 画像の読み込み
        void LoadGraphHandle( const image::ImageData& registData ) {
            imageDataList.emplace_back( LoadGraph( registData.filePath.c_str() ), registData.name );
        }

        /// @brief 読み込んだ画像を全て解放
        void Reset() {
            InitGraph();
            imageDataList.clear();
        }

       private:
        std::vector<RegistImageData> imageDataList {};
    };
}  // namespace shooting

#endif  // !IMAGE_MANAGER_H
