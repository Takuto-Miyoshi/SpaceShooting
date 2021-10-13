#include "EnemyManager.h"

#include <algorithm>

#include "../Manager/TimeManager.h"
#include "../Object/Actor/Enemy/ExplodeEnemy.h"
#include "../Object/Actor/Enemy/StandardEnemy.h"
#include "../Utility/Functions.h"
#include "DxLib.h"

namespace shooting::object {
    void EnemyManager::Initialize() {
        lotteryBox.reserve( Lottery::BOX_CAPACITY );
        box.reserve( Lottery::BOX_CAPACITY );

        spawnTimer = ObjectSetting::SPAWN_INTERVAL;
    }

    void EnemyManager::Update() {
        spawnTimer -= TimeManager::Instance()->DeltaTime;

        if ( spawnTimer <= 0 ) {
            spawnTimer = interval;

            auto enemy = Lottery();
            Generate( enemy );
            interval = enemy.NextInterval;
        }
    }
    void EnemyManager::Reset() {
        lotteryBox.clear();
    }

    auto EnemyManager::Lottery() -> status::SpawnData {
        box.clear();
        box.resize( lotteryBox.size() );

        // 確率に応じて本抽選リストに登録
        std::copy_if( lotteryBox.begin(), lotteryBox.end(), box.begin(), [this]( auto& element ) { return HitOfTheTime( element.SpawnRate ); } );

        return ( box.empty() ) ? lotteryBox.front() : box.at( GetRand( static_cast<int32_t>( box.size() - 1 ) ) );
    }

    void EnemyManager::Generate( status::SpawnData spawnData ) {
        GenerateByType( spawnData );

        if ( HitOfTheTime( spawnData.ChainRate ) ) {
            spawnData.ChainRate *= DECREASE_RATE;
            Generate( spawnData );
        }
    }

    void EnemyManager::GenerateByType( const status::SpawnData& spawnData ) {
        EnemyBase* enemy = nullptr;
        switch ( spawnData.SpawnType ) {
            case status::enemy::Type::StandardEnemy: enemy = GenerateEnemy<StandardEnemy>(); break;
            case status::enemy::Type::ExplodeEnemy: enemy = GenerateEnemy<ExplodeEnemy>(); break;
            default: return;
        }
        LevelSetting( *enemy, spawnData );
    }

    auto EnemyManager::HitOfTheTime( const double& chance ) -> bool {
        return chance >= GetRand( 100 );
    }

    auto EnemyManager::RandomPosition() -> Vector2 {
        Vector2 result;
        do {
            // 有効範囲内の位置を生成
            result.Set( Random<double>( ObjectSetting::VALID_DISTANCE ), Random<double>( ObjectSetting::VALID_DISTANCE ) );
        } while ( result.Length() >= ObjectSetting::VALID_DISTANCE );

        return result;
    }

    void EnemyManager::LevelSetting( EnemyBase& enemy, const status::SpawnData& spawnData ) {
        // 1~100の値で設定
        enemy.Level = Random<uint32_t>( spawnData.MinLevel, spawnData.MaxLevel );
    }
}  // namespace shooting::object
