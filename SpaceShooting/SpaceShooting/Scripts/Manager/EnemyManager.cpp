#include "EnemyManager.h"

#include <algorithm>

#include "../Definition/StatusDefinition.h"
#include "../Manager/ObjectManager.h"
#include "../Manager/TimeManager.h"
#include "../Object/Actor/ExplodeEnemy.h"
#include "../Object/Actor/StandardEnemy.h"
#include "DxLib.h"

namespace shooting::object {
    void EnemyManager::Initialize() {
        lotteryBox.reserve( Lottery::BOX_CAPACITY );
        box.reserve( Lottery::BOX_CAPACITY );
    }

    void EnemyManager::Update() {
        spawnTimer -= TimeManager::Instance()->DeltaTime;

        if ( spawnTimer <= 0 ) {
            spawnTimer = Object::SPAWN_INTERVAL;

            auto enemy = Lottery();
            Generate( enemy.type, enemy.chainChance );
        }
    }

    void EnemyManager::Register( EnemyType&& type, const double& spawnChance, const double& chainChance ) {
        // 重複要素を排除
        Unregister( type );

        lotteryBox.emplace_back( type, spawnChance, chainChance );
    }

    void EnemyManager::Unregister( const EnemyType& type ) {
        std::erase_if( lotteryBox, [&type]( auto& element ) { return element.type == type; } );
    }

    void EnemyManager::Reset() {
        lotteryBox.clear();
    }

    auto EnemyManager::Lottery() -> LotteryData {
        box.clear();
        box.resize( lotteryBox.size() );

        // 確率に応じて本抽選リストに登録
        std::copy_if( lotteryBox.begin(), lotteryBox.end(), box.begin(), [this]( auto& element ) { return HitOfTheTime( element.spawnChance ); } );

        if ( box.empty() ) { return lotteryBox.front(); }
        return box.at( GetRand( static_cast<int32_t>( box.size() - 1 ) ) );
    }

    void EnemyManager::Generate( const EnemyType& type, double chainChance ) {
        GenerateByType( type );

        if ( HitOfTheTime( chainChance ) ) {
            chainChance *= DECREASE_RATE;
            Generate( type, chainChance );
        }
    }

    void EnemyManager::GenerateByType( const EnemyType& type ) {
        auto objectManager = ObjectManager::Instance();
        switch ( type ) {
            case EnemyType::StandardEnemy: objectManager->CreateObject<StandardEnemy>( status::ObjectKind::Enemy, RandomPosition() ); break;
            case EnemyType::ExplodeEnemy: objectManager->CreateObject<ExplodeEnemy>( status::ObjectKind::Enemy, RandomPosition() ); break;
            default: break;
        }
    }

    auto EnemyManager::HitOfTheTime( const double& chance ) -> bool {
        return chance >= GetRand( 100 );
    }

    auto EnemyManager::RandomPosition() -> Vector2 {
        Vector2 result;
        do {
            // 有効範囲内の位置を生成
            result = Vector2 { static_cast<double>( GetRand( static_cast<int32_t>( Object::VALID_DISTANCE ) ) ) - Object::VALID_DISTANCE,
                               static_cast<double>( GetRand( static_cast<int32_t>( Object::VALID_DISTANCE ) ) ) - Object::VALID_DISTANCE };
        } while ( result.Length() >= Object::VALID_DISTANCE );

        return result;
    }
}  // namespace shooting::object
