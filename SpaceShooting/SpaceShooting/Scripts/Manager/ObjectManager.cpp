#include "ObjectManager.h"

#include "../Definition/StatusDefinition.h"
#include "../Object/Actor/EnemyBase.h"
#include "../Object/Bullet/BulletBase.h"

namespace shooting::object {
    void ObjectManager::Initialize() {
        objectList.reserve( Object::OBJECT_CAPACITY );
        playerBulletList.reserve( Object::OBJECT_CAPACITY );
        enemyList.reserve( Object::OBJECT_CAPACITY );
        enemyBulletList.reserve( Object::OBJECT_CAPACITY );

        EnemyBase::LoadEnemyData();
        BulletBase::LoadBulletData();
    }

    void ObjectManager::Update() {
        for ( auto&& obj : std::as_const( objectList ) ) {
            obj->ReserveStart();
            obj->CheckOutOfValidArea();
            obj->Update();
        }

        CollisionDetection();

        EraseUnactiveObject();
    }

    void ObjectManager::Draw() {
        for ( auto&& obj : std::as_const( objectList ) ) {
            obj->Draw();
        }

        printfDx( "object : %d\n", objectList.size() );
    }

    void ObjectManager::Finalize() {
        objectList.clear();
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
                if ( Detection( *player, *bullet ) ) {
                    player->Collide( *bullet );
                    bullet->Collide( *player );
                }
            }
        }

        // Enemy * PlayerBullet
        if ( !enemyList.empty() && !playerBulletList.empty() ) {
            for ( auto&& enemy : std::as_const( enemyList ) ) {
                for ( auto&& bullet : std::as_const( playerBulletList ) ) {
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
        return ( objA.Position->VectorTo( objB.Position ).Length() <= ( objA.CollisionRadius + objB.CollisionRadius ) );
    }
}  // namespace shooting::object
