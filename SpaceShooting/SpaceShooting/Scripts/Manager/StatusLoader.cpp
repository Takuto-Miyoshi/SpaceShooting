#include "StatusLoader.h"

#include <algorithm>

#include "../Utility/Functions.h"
#include "DxLib.h"

using namespace shooting::object::status::loaderKey;

namespace shooting::object::status {
    void StatusLoader::Load() {
        if ( loaded ) { return; }

        // オブジェクトのステータスを読み取る
        currentRead = loaderKey::read::STATUS;
        file.open( path::STATUS );

        CheckCommandToStart();

        do {
            ReadData();
            NextLine();
        } while ( CheckRowCommand() );

        file.close();
        Reset();

        // 敵出現情報を読み取る
        currentRead = loaderKey::read::SPAWN;
        file.open( path::SPAWN );

        CheckCommandToStart();

        do {
            ReadData();
            NextLine();
        } while ( CheckRowCommand() );

        file.close();

        // 読み込み完了
        loaded = true;
    }

    void StatusLoader::CheckColumnCommand() {
        while ( ReadElement() ) {
            if ( SameBuffer( command::SKIP ) ) {
                // スキップする列を記録
                skipIndex.push_back( columnIndex );
            }

            columnIndex++;
        }
    }

    void StatusLoader::ReadConstantData() {
        auto number { 0u };
        while ( ReadElement() ) {
            if ( CanReadTarget() ) {
                // パラメータに番号を振る
                if ( SameCurrentRead( loaderKey::read::STATUS ) ) {
                    parameter::List.at( buffer.String ) = number;
                }
                else if ( SameCurrentRead( loaderKey::read::SPAWN ) ) {
                    spawn::List.at( buffer.String ) = number;
                }

                number++;
            }
            columnIndex++;
        }
    }

    void StatusLoader::CheckCommandToStart() {
        while ( NextLine() ) {
            ReadElement();
            columnIndex = 0;
            if ( SameBuffer( command::START ) ) {
                return;
            }
            else if ( SameBuffer( command::COMMAND ) ) {
                CheckColumnCommand();
            }
            else if ( SameBuffer( command::CONSTANT ) ) {
                ReadConstantData();
            }
        }
    }

    void StatusLoader::ReadData() {
        columnIndex = 0;
        while ( ReadElement() ) {
            if ( CanReadTarget() ) {
                buffer.Contents.push_back( buffer.String );
            }
            columnIndex++;
        }

        if ( SameCurrentRead( loaderKey::read::STATUS ) ) {
            readedObjectList.push_back( TranslateObjectBuffer() );
        }
        else if ( SameCurrentRead( loaderKey::read::SPAWN ) ) {
            readedSpawnDataList.push_back( TranslateSpawnBuffer() );
        }

        buffer.Contents.clear();
    }

    auto StatusLoader::NextLine() -> bool {
        std::getline( file, buffer.String );
        buffer.Line.clear();
        buffer.Line.str( buffer.String );
        return !file.eof();
    }

    auto StatusLoader::ReadElement() -> bool {
        return !std::getline( buffer.Line, buffer.String, command::BREAK ).fail();
    }

    auto StatusLoader::CheckRowCommand() -> bool {
        ReadElement();
        if ( SameBuffer( command::SKIP ) ) {
            // 次の行へ→コマンド確認
            NextLine();
            return CheckRowCommand();
        }
        else if ( SameBuffer( command::END ) ) {
            // 読み取り終了
            return false;
        }

        // 読み取りを続ける
        return true;
    }

    auto StatusLoader::TranslateObjectBuffer() -> ObjectStates {
        ObjectStates states {};

        states.Category = buffer.Get<std::string>( parameter::CATEGORY );
        states.Name = buffer.Get<std::string>( parameter::NAME );
        states.Id = buffer.Get<uint32_t>( parameter::ID );

        states.ObjectData.CollisionRadius = buffer.Get<double>( parameter::object::COLLISION_RADIUS );
        const auto path { buffer.Get<std::string>( parameter::object::GRAPHIC_PATH ) };
        if ( path != command::NONE ) [[likely]] {
            states.ObjectData.GraphicHandle = LoadGraph( path.c_str() );
        }

        states.ActorData.MaxHp = buffer.Get<double>( parameter::actor::MAX_HP );
        states.ActorData.Hp = buffer.Get<double>( parameter::actor::HP );
        states.ActorData.Speed = buffer.Get<double>( parameter::actor::SPEED );
        states.ActorData.GrowHp.Fixed = buffer.Get<double>( parameter::actor::grow::FIXED );
        states.ActorData.GrowHp.Fluctuation = buffer.Get<double>( parameter::actor::grow::FLUCTUATION );
        states.ActorData.GrowHp.UseRatio = buffer.Get<double>( parameter::actor::grow::USE_RATIO );

        states.BulletData.Speed = buffer.Get<double>( parameter::bullet::SPEED );
        states.BulletData.AttackPower = buffer.Get<double>( parameter::bullet::ATTACK_POWER );
        states.BulletData.Acceleration = buffer.Get<double>( parameter::bullet::ACCELERATION );
        states.BulletData.AngularVelocity = buffer.Get<float>( parameter::bullet::ANGULER_VELOCITY );
        states.BulletData.BulletType = buffer.Get<bullet::Type>( parameter::bullet::TYPE );
        states.BulletData.GrowAttackPower.Fixed = buffer.Get<double>( parameter::bullet::grow::FIXED );
        states.BulletData.GrowAttackPower.Fluctuation = buffer.Get<double>( parameter::bullet::grow::FLUCTUATION );
        states.BulletData.GrowAttackPower.UseRatio = buffer.Get<double>( parameter::bullet::grow::USE_RATIO );

        states.EnemyData.Exp = buffer.Get<uint32_t>( parameter::enemy::EXP );
        states.EnemyData.Interval = buffer.Get<double>( parameter::enemy::INTERVAL );

        states.WeaponData.Interval = buffer.Get<double>( parameter::weapon::INTERVAL );
        states.WeaponData.Rarity = buffer.Get<uint32_t>( parameter::weapon::RARITY );

        states.ExtraParam1 = buffer.Get<double>( parameter::extra::PARAM1 );
        states.ExtraParam2 = buffer.Get<double>( parameter::extra::PARAM2 );
        states.ExtraParam3 = buffer.Get<double>( parameter::extra::PARAM3 );

        return states;
    }

    auto StatusLoader::TranslateSpawnBuffer() -> SpawnData {
        SpawnData data {};

        data.Group = buffer.Get<uint32_t>( spawn::GROUP, read::SPAWN );
        data.SpawnType = buffer.Get<status::enemy::Type>( spawn::SPAWN_TYPE, read::SPAWN );
        data.SpawnRate = buffer.Get<double>( spawn::SPAWN_RATE, read::SPAWN );
        data.ChainRate = buffer.Get<double>( spawn::CHAIN_RATE, read::SPAWN );
        data.MinLevel = buffer.Get<uint32_t>( spawn::MIN_LEVEL, read::SPAWN );
        data.MaxLevel = buffer.Get<uint32_t>( spawn::MAX_LEVEL, read::SPAWN );
        data.NextInterval = buffer.Get<double>( spawn::NEXT_INTERVAL, read::SPAWN );

        return data;
    }

    void StatusLoader::Reset() noexcept {
        buffer.Contents.clear();
        buffer.Line.clear();
        buffer.String.clear();

        file.clear();
        columnIndex = 0;
        skipIndex.clear();
    }

    constexpr auto StatusLoader::CanReadTarget() -> bool {
        return !std::any_of( skipIndex.begin(), skipIndex.end(), [this]( const auto& element ) { return columnIndex == element; } );
    }

    constexpr auto StatusLoader::SameCurrentRead( const std::string& read ) noexcept -> bool {
        return EqualString( currentRead, read );
    }

    constexpr auto StatusLoader::SameBuffer( const std::string& str ) noexcept -> bool {
        return EqualString( buffer.String, str );
    }

}  // namespace shooting::object::status
