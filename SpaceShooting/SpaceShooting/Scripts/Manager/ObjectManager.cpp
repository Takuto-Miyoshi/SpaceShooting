#include "ObjectManager.h"

#include "../Definition/StatusDefinition.h"
#include "../Object/Actor/Enemy/EnemyBase.h"
#include "../Object/Actor/Player.h"
#include "../Object/Bullet/BulletBase.h"

namespace shooting::object {
    void ObjectManager::Initialize() {
        objectList.reserve( ObjectSetting::OBJECT_CAPACITY );
        playerBulletList.reserve( ObjectSetting::OBJECT_CAPACITY );
        enemyList.reserve( ObjectSetting::OBJECT_CAPACITY );
        enemyBulletList.reserve( ObjectSetting::OBJECT_CAPACITY );
    }

    void ObjectManager::Update() {
        for ( auto&& obj : std::as_const( objectList ) ) {
            if ( !obj ) { continue; }
            obj->ReserveStart();
            obj->CheckOutOfValidArea();
            obj->Update();
        }

        CollisionDetection();

        EraseUnactiveObject();
    }

    void ObjectManager::Draw() {
        for ( auto&& obj : std::as_const( objectList ) ) {
            if ( !obj ) { continue; }
            obj->Draw();
        }
    }

    void ObjectManager::Finalize() {
        objectList.clear();
    }

    void ObjectManager::GiveExp( const int32_t& exp ) {
        dynamic_cast<Player*>( &*player )->AddExp( exp );
    }

    void ObjectManager::EraseUnactiveObject() {
        std::erase_if( objectList, []( auto& element ) {
            return !element->IsActive;
        } );
    }

    void ObjectManager::CollisionDetection() {
        Grouping();

        // Player * EnemyBullet
        if ( !enemyBulletList.empty() && player ) {
            for ( auto&& bullet : std::as_const( enemyBulletList ) ) {
                if ( !bullet ) { continue; }
                if ( Detection( *player, *bullet ) ) {
                    player->Collide( *bullet );
                    bullet->Collide( *player );
                }
            }
        }

        // Enemy * PlayerBullet
        if ( !enemyList.empty() && !playerBulletList.empty() ) {
            for ( auto&& enemy : std::as_const( enemyList ) ) {
                if ( !enemy ) { continue; }
                for ( auto&& bullet : std::as_const( playerBulletList ) ) {
                    if ( !bullet ) { continue; }
                    if ( Detection( *enemy, *bullet ) ) {
                        enemy->Collide( *bullet );
                        bullet->Collide( *enemy );
                    }
                }
            }
        }
    }

    void ObjectManager::Grouping() {
        playerBulletList.clear();
        enemyList.clear();
        enemyBulletList.clear();

        // グループに分ける
        for ( auto&& obj : std::as_const( objectList ) ) {
            switch ( obj->Kind ) {
                case status::ObjectKind::Player:
                    player = obj;
                    break;
                case status::ObjectKind::PlayerBullet:
                    playerBulletList.emplace_back( obj );
                    break;
                case status::ObjectKind::Enemy:
                    enemyList.emplace_back( obj );
                    break;
                case status::ObjectKind::EnemyBullet:
                    enemyBulletList.emplace_back( obj );
                    break;
            }
        }
    }

    auto ObjectManager::Detection( const ObjectBase& objA, const ObjectBase& objB ) const -> bool {
        return ( objA.Position->To( objB.Position ).Length() <= ( objA.ObjectStatus->CollisionRadius + objB.ObjectStatus->CollisionRadius ) );
    }
}  // namespace shooting::object
