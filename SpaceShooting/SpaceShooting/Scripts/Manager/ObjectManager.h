// オブジェクトの管理

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <algorithm>
#include <memory>
#include <vector>

#include "../Object/ObjectBase.h"
#include "../Utility/Singleton.h"
#include "../Utility/Vector.h"

namespace shooting::object {
    class ObjectManager : public Singleton<ObjectManager> {
       public:
        ObjectManager() = default;

        ~ObjectManager() = default;

       public:
        void Initialize();

        /// @brief オブジェクトを作成
        /// @tparam T 作成するオブジェクトの型 @n ObjectBaseを基底クラスに持っていること
        template<typename T>
        auto CreateObject( const status::ObjectKind& objectKind, const Vector2& position = Vector2( 0, 0 ), const float& angle = 0.0f ) -> std::enable_if<std::derived_from<T, ObjectBase>, ObjectBase>::type* {
            auto obj = std::make_shared<T>();
            obj->Activate( objectKind, position, angle );
            objectList.emplace_back( obj );
            return &*objectList.back();
        }

        /// @brief 更新
        void Update();

        /// @brief 描画
        void Draw();

        /// @brief 終了処理
        void Finalize();

        /// @brief プレイヤーの位置を取得
        /// @return プレイヤーが見つからなければVector2{0,0}を返す
        [[nodiscard]] auto PlayerPosition() -> Vector2 {
            return ( player ) ? player->Position : Vector2::Zero();
        }

        /// @brief プレイヤーに経験値を付与
        void GiveExp( const uint32_t& exp );

        /// @brief fromから一番近い敵(ObjectKind::Enemy)の位置を取得
        /// @return 敵がいなければVector2{0,0}を返す
        [[nodiscard]] auto NearEnemyPosition( const Vector2& from ) -> Vector2 {
            if ( enemyList.empty() ) { return Vector2::Zero(); }

            return std::min_element( enemyList.begin(), enemyList.end(), [&from]( auto& left, auto& right ) {
                       return from.To( left->Position ).Length() < from.To( right->Position ).Length();
                   } )
                ->get()
                ->Position;
        }

       private:
        /// @brief アクティブでないオブジェクトをリストから削除
        void EraseUnactiveObject();

        /// @brief 全てのオブジェクトに当たり判定処理を実行
        void CollisionDetection();

        /// @brief オブジェクトをグループに分ける
        void Grouping();

        /// @brief 2つのオブジェクトが接触しているかを取得
        auto Detection( const ObjectBase& objA, const ObjectBase& objB ) const -> bool;

       private:
        std::vector<std::shared_ptr<ObjectBase>> objectList;  // オブジェクト全体

        std::shared_ptr<ObjectBase> player;
        std::vector<std::shared_ptr<ObjectBase>> playerBulletList;
        std::vector<std::shared_ptr<ObjectBase>> enemyList;
        std::vector<std::shared_ptr<ObjectBase>> enemyBulletList;
    };
}  // namespace shooting::object

#endif  // !OBJECT_MANAGER_H
