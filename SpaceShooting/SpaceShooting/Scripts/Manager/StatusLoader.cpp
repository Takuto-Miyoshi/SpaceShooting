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
        uint32_t number = 0;
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

        states.Category = buffer.StringFrom( parameter::Category );
        states.Name = buffer.StringFrom( parameter::Name );
        states.Id = buffer.UIntFrom( parameter::Id );

        states.ObjectData.CollisionRadius = buffer.DoubleFrom( parameter::object::CollisionRadius );
        auto path = buffer.StringFrom( parameter::object::GraphicPath );
        if ( path != command::NONE ) {
            states.ObjectData.GraphicHandle = LoadGraph( path.c_str() );
        }

        states.ActorData.MaxHp = buffer.DoubleFrom( parameter::actor::MaxHp );
        states.ActorData.Hp = buffer.DoubleFrom( parameter::actor::Hp );
        states.ActorData.Speed = buffer.DoubleFrom( parameter::actor::Speed );
        states.ActorData.GrowHp.Fixed = buffer.DoubleFrom( parameter::actor::grow::Fixed );
        states.ActorData.GrowHp.Fluctuation = buffer.DoubleFrom( parameter::actor::grow::Fluctuation );
        states.ActorData.GrowHp.UseRatio = buffer.DoubleFrom( parameter::actor::grow::UseRatio );

        states.BulletData.Speed = buffer.DoubleFrom( parameter::bullet::Speed );
        states.BulletData.AttackPower = buffer.DoubleFrom( parameter::bullet::AttackPower );
        states.BulletData.Acceleration = buffer.DoubleFrom( parameter::bullet::Acceleration );
        states.BulletData.AngularVelocity = buffer.FloatFrom( parameter::bullet::AngulerVelocity );
        states.BulletData.BulletType = buffer.EnumFrom<bullet::Type>( parameter::bullet::Type );
        states.BulletData.GrowAttackPower.Fixed = buffer.DoubleFrom( parameter::bullet::grow::Fixed );
        states.BulletData.GrowAttackPower.Fluctuation = buffer.DoubleFrom( parameter::bullet::grow::Fluctuation );
        states.BulletData.GrowAttackPower.UseRatio = buffer.DoubleFrom( parameter::bullet::grow::UseRatio );

        states.EnemyData.Exp = buffer.UIntFrom( parameter::enemy::Exp );
        states.EnemyData.Interval = buffer.DoubleFrom( parameter::enemy::Interval );

        states.WeaponData.Interval = buffer.DoubleFrom( parameter::weapon::Interval );
        states.WeaponData.Rarity = buffer.UIntFrom( parameter::weapon::Rarity );

        states.ExtraParam1 = buffer.DoubleFrom( parameter::extra::Param1 );
        states.ExtraParam2 = buffer.DoubleFrom( parameter::extra::Param2 );
        states.ExtraParam3 = buffer.DoubleFrom( parameter::extra::Param3 );

        return states;
    }

    auto StatusLoader::TranslateSpawnBuffer() -> SpawnData {
        SpawnData data {};

        data.Group = buffer.UIntFrom( spawn::GROUP, read::SPAWN );
        data.SpawnType = buffer.EnumFrom<status::enemy::Type>( spawn::SPAWN_TYPE, read::SPAWN );
        data.SpawnRate = buffer.DoubleFrom( spawn::SPAWN_RATE, read::SPAWN );
        data.ChainRate = buffer.DoubleFrom( spawn::CHAIN_RATE, read::SPAWN );
        data.MinLevel = buffer.UIntFrom( spawn::MIN_LEVEL, read::SPAWN );
        data.MaxLevel = buffer.UIntFrom( spawn::MAX_LEVEL, read::SPAWN );
        data.NextInterval = buffer.DoubleFrom( spawn::NEXT_INTERVAL, read::SPAWN );

        return data;
    }

    void StatusLoader::Reset() {
        buffer.Contents.clear();
        buffer.Line.clear();
        buffer.String.clear();

        file.clear();
        columnIndex = 0;
        skipIndex.clear();
    }

    constexpr auto StatusLoader::SameCurrentRead( const std::string& read ) -> bool {
        return EqualString( currentRead, read );
    }

    constexpr auto StatusLoader::CanReadTarget() -> bool {
        return !std::any_of( skipIndex.begin(), skipIndex.end(), [this]( auto& element ) { return columnIndex == element; } );
    }

    constexpr auto StatusLoader::SameBuffer( const std::string& str ) -> bool {
        return EqualString( buffer.String, str );
    }

}  // namespace shooting::object::status
