#include "EnemyManager.h"

#include <algorithm>

#include "../Object/Actor/Enemy/ExplodeEnemy.h"
#include "../Object/Actor/Enemy/Ghost.h"
#include "../Object/Actor/Enemy/Magician.h"
#include "../Object/Actor/Enemy/NeedleEnemy.h"
#include "../Object/Actor/Enemy/StandardEnemy.h"
#include "../Utility/Functions.h"
#include "DxLib.h"

namespace shooting::object {
    void EnemyManager::Initialize() {
        lotteryBox.reserve( Lottery::BOX_CAPACITY );
        box.reserve( Lottery::BOX_CAPACITY );

        interval = ObjectSetting::SPAWN_INTERVAL;
    }

    void EnemyManager::Reset() noexcept {
        lotteryBox.clear();
    }

    void EnemyManager::Spawn() {
        auto&& enemy { Lottery() };
        Generate( enemy );
        interval = enemy.NextInterval;
    }

    auto EnemyManager::Lottery() -> const status::SpawnData& {
        box.clear();

        // 確率に応じて本抽選リストに登録
        for ( auto&& element : lotteryBox ) {
            if ( HitOfTheTime( element.SpawnRate ) ) {
                box.push_back( element );
            }
        }

        // 抽選
        return ( box.empty() ) ? lotteryBox.front() : box.at( Random<uint64_t>( 0, box.size() - 1 ) );
    }

    void EnemyManager::Generate( status::SpawnData spawnData ) {
        GenerateByType( spawnData );

        if ( HitOfTheTime( spawnData.ChainRate ) ) {
            spawnData.ChainRate *= DECREASE_RATE;
            Generate( spawnData );
        }
    }

    void EnemyManager::GenerateByType( const status::SpawnData& spawnData ) {
        EnemyBase* enemy { nullptr };
        switch ( spawnData.SpawnType ) {
            case status::enemy::Type::StandardEnemy: enemy = GenerateEnemy<StandardEnemy>(); break;
            case status::enemy::Type::ExplodeEnemy: enemy = GenerateEnemy<ExplodeEnemy>(); break;
            case status::enemy::Type::NeedleEnemy: enemy = GenerateEnemy<NeedleEnemy>(); break;
            case status::enemy::Type::Magician: enemy = GenerateEnemy<Magician>(); break;
            case status::enemy::Type::Ghost: enemy = GenerateEnemy<Ghost>(); break;
            default: return;
        }
        LevelSetting( *enemy, spawnData );
    }

    auto EnemyManager::HitOfTheTime( const double& chance ) -> bool {
        return chance >= Random<double>( 0.0, 100.0 );
    }

    auto EnemyManager::RandomPosition() -> Vector2<double> {
        Vector2 result {};
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
