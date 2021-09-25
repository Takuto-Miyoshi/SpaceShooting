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
        template<class T>
        auto CreateObject( const status::ObjectKind& objectKind, const Vector2& position = Vector2( 0, 0 ), const float& angle = 0.0f ) -> ObjectBase* {
            auto obj = std::make_shared<T>();
            obj->Activate( objectKind, position, angle );
            objectList.emplace_back( obj );
            return &*objectList.back();
        }

        void Update();

        void Draw();

        void Finalize();

        [[nodiscard]] auto PlayerPosition() -> Vector2 {
            return ( player ) ? player->Position : Vector2 { 0, 0 };
        }

        [[nodiscard]] auto NearEnemyPosition( const Vector2& from ) -> Vector2 {
            Grouping();
            if ( enemyList.empty() ) { return Vector2 { 0, 0 }; }
            return std::min_element( enemyList.begin(), enemyList.end(), [&from]( auto& left, auto& right ) {
                       return from.VectorTo( left->Position ).Length() < from.VectorTo( right->Position ).Length();
                   } )
                ->get()
                ->Position;
        }

       private:
        /// @brief アクティブでないオブジェクトをリストから削除
        void EraseUnactiveObject();

        void CollisionDetection();

        void Grouping();

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
