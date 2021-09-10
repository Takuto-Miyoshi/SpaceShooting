// 弾を管理する

#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include <algorithm>
#include <memory>
#include <vector>

#include "../Definition/StatusDefinition.h"
#include "../Object/Bullet/BulletBase.h"
#include "../Object/Bullet/StandardBullet.h"
#include "../Utility/Singleton.h"

namespace shooting::object {
    class BulletManager : public Singleton<BulletManager> {
       public:
        BulletManager() = default;

        ~BulletManager() = default;

       public:
        void Initialize() {
            BulletBase::LoadBulletData();

            bullets = std::vector<std::unique_ptr<BulletBase>>();
            for ( uint32_t i = 0; i < DEFAULT_MAGAZINE; i++ ) {
                bullets.push_back( std::make_unique<BulletBase>() );
            }
        }

        void Update() {
            std::for_each( bullets.begin(), bullets.end(), []( auto& element ) {
                element->ReserveStart();
                element->Update();
            } );
        }

        void Draw() {
            std::for_each( bullets.begin(), bullets.end(), []( auto& element ) {
                element->Draw();
            } );
        }

        /// @brief 弾を生成する
        void Generate( status::BulletType bulletType, Vector2 position, float angle ) {
            auto space = UnUsedSpace();

            switch ( bulletType ) {
                case status::BulletType::StandardBullet:
                    *space = std::make_unique<StandardBullet>();
                    break;
            }

            space->get()->Activate( position, angle );
        }

       private:
        /// @brief 空きスペースを取得 @n なければ拡張
        auto UnUsedSpace() -> std::vector<std::unique_ptr<BulletBase>>::iterator {
            auto result = std::find_if( bullets.begin(), bullets.end(), []( auto& element ) {
                return !element->IsActive;
            } );

            // 最後の要素を警戒
            if ( result == bullets.end() ) {
                bullets.push_back( std::make_unique<BulletBase>() );
                result = bullets.end() - 1;
            }

            return result;
        }

       private:
        static constexpr int32_t DEFAULT_MAGAZINE = 300;
        std::vector<std::unique_ptr<BulletBase>> bullets;
    };
}  // namespace shooting::object

#endif  // !BULLET_MANAGER_H
