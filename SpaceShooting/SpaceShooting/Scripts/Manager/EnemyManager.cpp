#include "EnemyManager.h"

#include <algorithm>

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
        spawnTimer += TimeManager::Instance()->DeltaTime;

        if ( spawnTimer >= ObjectSetting::SPAWN_INTERVAL ) {
            spawnTimer = 0;

            auto enemy = Lottery();
            Generate( enemy.type, enemy.chainChance );
        }
    }

    void EnemyManager::Register( status::enemy::Type&& type, const double& spawnChance, const double& chainChance ) {
        // 重複要素を排除
        Unregister( type );

        lotteryBox.emplace_back( type, spawnChance, chainChance );
    }

    void EnemyManager::Unregister( const status::enemy::Type& type ) {
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

        return ( box.empty() ) ? lotteryBox.front() : box.at( GetRand( static_cast<int32_t>( box.size() - 1 ) ) );
    }

    void EnemyManager::Generate( const status::enemy::Type& type, double chainChance ) {
        GenerateByType( type );

        if ( HitOfTheTime( chainChance ) ) {
            chainChance *= DECREASE_RATE;
            Generate( type, chainChance );
        }
    }

    void EnemyManager::GenerateByType( const status::enemy::Type& type ) {
        auto objectManager = ObjectManager::Instance();
        switch ( type ) {
            case status::enemy::Type::StandardEnemy: objectManager->CreateObject<StandardEnemy>( status::ObjectKind::Enemy, RandomPosition() ); break;
            case status::enemy::Type::ExplodeEnemy: objectManager->CreateObject<ExplodeEnemy>( status::ObjectKind::Enemy, RandomPosition() ); break;
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
            result = Vector2 { static_cast<double>( GetRand( static_cast<int32_t>( ObjectSetting::VALID_DISTANCE ) ) ) - ObjectSetting::VALID_DISTANCE,
                               static_cast<double>( GetRand( static_cast<int32_t>( ObjectSetting::VALID_DISTANCE ) ) ) - ObjectSetting::VALID_DISTANCE };
        } while ( result.Length() >= ObjectSetting::VALID_DISTANCE );

        return result;
    }
}  // namespace shooting::object
