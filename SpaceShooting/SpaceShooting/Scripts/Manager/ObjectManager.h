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
        void CreateObject( const Vector2& position = Vector2( 0, 0 ), const float& angle = PI / 2 ) {
            auto obj = std::make_shared<T>();
            obj->Activate( position, angle );
            objectList.emplace_back( obj );
        }

        void Update();

        void Draw();

        void Finalize();

       private:
        /// @brief アクティブでないオブジェクトをリストから削除
        void EraseUnactiveObject();

       private:
        std::vector<std::shared_ptr<ObjectBase>> objectList;  // オブジェクト全体
    };
}  // namespace shooting::object

#endif  // !OBJECT_MANAGER_H
