// CSVファイルからステータスを読み込む

#ifndef STATUS_LOADER_H
#define STATUS_LOADER_H

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../Definition/StatusDefinition.h"
#include "../Definition/StatusLoaderKey.h"
#include "../Utility/Singleton.h"

namespace shooting::object::status {
    class StatusLoader : public Singleton<StatusLoader> {
       public:
        struct ObjectStates {
            std::string Category {};
            std::string Name {};
            uint32_t Id { 0 };

            Object ObjectData {};
            Actor ActorData {};
            Bullet BulletData {};
            Enemy EnemyData {};
            Weapon WeaponData {};

            double ExtraParam1 { 0.0 };
            double ExtraParam2 { 0.0 };
            double ExtraParam3 { 0.0 };
        };

       public:
        StatusLoader() = default;

        ~StatusLoader() = default;

       public:
        void Load();

        /// @brief オブジェクトのデータを参照 @n StatusLoaderKey::loaderKey::object::XXXX
        auto Get_a( const std::string& objectName ) -> const ObjectStates& {
            return *std::find_if( readedObjectList.begin(), readedObjectList.end(), [&objectName]( auto& element ) { return element.Name == objectName; } );
        }

        /// @brief 武器のデータを参照 @n StatusLoaderKey::loaderKey::object::XXXX
        auto Get_a( const std::string& objectName, const uint32_t& rarity ) -> const ObjectStates& {
            return *std::find_if( readedObjectList.begin(), readedObjectList.end(),
                                  [&objectName, &rarity]( auto& element ) { return element.Name == objectName && element.WeaponData.Rarity == rarity; } );
        }

        /// @brief スポーンデータのリストを取得
        auto GetGroup( const uint32_t& groupId ) -> const std::vector<SpawnData> {
            std::vector<SpawnData> result;
            for ( auto&& element : std::as_const( readedSpawnDataList ) ) {
                if ( element.Group == groupId ) {
                    result.push_back( element );
                }
            }

            return result;
        }

       private:
        /// @brief 列コマンドを確認
        void CheckColumnCommand();

        /// @brief 定数データを読み取り更新
        void ReadConstantData();

        /// @brief "start"までの行コマンドを確認する
        void CheckCommandToStart();

        /// @brief 一行読み取り格納する
        void ReadData();

        /// @brief 次の行へ
        /// @return ファイルが終わりならfalse
        auto NextLine() -> bool;

        /// @brief 一要素(次の区切り文字まで)読み取る
        /// @return 読み取りに失敗したらfalse
        auto ReadElement() -> bool;

        /// @brief 行コマンドを確認
        auto CheckRowCommand() -> bool;

        /// @brief stringBufferをObjectStatesに翻訳して返す
        auto TranslateObjectBuffer() -> ObjectStates;

        /// @brief stringBufferをSpawnDataに翻訳して返す
        auto TranslateSpawnBuffer() -> SpawnData;

        void Reset();

        /// @brief currentReadと比較
        constexpr auto SameCurrentRead( const std::string& read ) -> bool;

        /// @brief columnIndexが読み取り対象かを調べる
        constexpr auto CanReadTarget() -> bool;

        /// @brief バッファの文字列と一致しているかを調べる
        constexpr auto SameBuffer( const std::string& str ) -> bool;

       private:
        struct {
            std::vector<std::string> Contents {};
            std::string String {};
            std::istringstream Line {};

            template<typename T = double>
            auto Get( const uint32_t& index ) const -> T {
                return static_cast<T>( Contents.at( index ) );
            }

            auto StringFrom( const std::string& parameterName, const std::string& readFor = loaderKey::read::STATUS ) -> std::string {
                if ( EqualString( readFor, loaderKey::read::STATUS ) ) {
                    return Contents.at( loaderKey::parameter::IdOn( parameterName ) );
                }
                else if ( EqualString( readFor, loaderKey::read::SPAWN ) ) {
                    return Contents.at( loaderKey::spawn::IdOn( parameterName ) );
                }

                return std::string( "" );
            }

            auto UIntFrom( const std::string& parameterName, const std::string& readFor = loaderKey::read::STATUS ) -> uint32_t {
                if ( EqualString( readFor, loaderKey::read::STATUS ) ) {
                    return std::stoul( Contents.at( loaderKey::parameter::IdOn( parameterName ) ) );
                }
                else if ( EqualString( readFor, loaderKey::read::SPAWN ) ) {
                    return std::stoul( Contents.at( loaderKey::spawn::IdOn( parameterName ) ) );
                }

                return 0;
            }

            auto DoubleFrom( const std::string& parameterName, const std::string& readFor = loaderKey::read::STATUS ) -> double {
                if ( EqualString( readFor, loaderKey::read::STATUS ) ) {
                    return std::stod( Contents.at( loaderKey::parameter::IdOn( parameterName ) ) );
                }
                else if ( EqualString( readFor, loaderKey::read::SPAWN ) ) {
                    return std::stod( Contents.at( loaderKey::spawn::IdOn( parameterName ) ) );
                }

                return 0.0;
            }

            auto FloatFrom( const std::string& parameterName, const std::string& readFor = loaderKey::read::STATUS ) -> float {
                if ( EqualString( readFor, loaderKey::read::STATUS ) ) {
                    return static_cast<float>( std::stod( Contents.at( loaderKey::parameter::IdOn( parameterName ) ) ) );
                }
                else if ( EqualString( readFor, loaderKey::read::SPAWN ) ) {
                    return static_cast<float>( std::stod( Contents.at( loaderKey::spawn::IdOn( parameterName ) ) ) );
                }

                return 0.0f;
            }

            template<typename T>
            auto EnumFrom( const std::string& parameterName, const std::string& readFor = loaderKey::read::STATUS ) -> typename std::enable_if<std::is_enum<T>::value, T>::type {
                if ( EqualString( readFor, loaderKey::read::STATUS ) ) {
                    return static_cast<T>( std::stoul( Contents.at( loaderKey::parameter::IdOn( parameterName ) ) ) );
                }
                else if ( EqualString( readFor, loaderKey::read::SPAWN ) ) {
                    return static_cast<T>( std::stoul( Contents.at( loaderKey::spawn::IdOn( parameterName ) ) ) );
                }

                return static_cast<T>( 0 );
            }
        } buffer;

        std::ifstream file {};  // 読み込む対象
        std::vector<uint32_t> skipIndex {};  // 読み込まない列リスト
        uint32_t columnIndex { 0 };  // 何列目を読み込んでいるか

        std::vector<ObjectStates> readedObjectList {};  // データを丸々入れておくリスト
        std::vector<SpawnData> readedSpawnDataList {};

        std::string currentRead {};

        bool loaded { false };  // ロード済みか
    };
}  // namespace shooting::object::status

#endif  // !STATUS_LOADER_H
