// オブジェクトの管理

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <algorithm>
#include <memory>
#include <vector>

#include "../Object/ObjectBase.h"
#include "../Utility/Singleton.h"

namespace shooting::object {
    class ObjectManager : public Singleton<ObjectManager> {
       public:
        ObjectManager() = default;

        ~ObjectManager() = default;

       public:
        void Initialize() {
            objectList = std::vector<std::shared_ptr<ObjectBase>>();
            processObjectList = std::vector<std::weak_ptr<ObjectBase>>();
        }

        template<class T>
        /// @brief オブジェクトを作成
        /// @tparam T 作成するオブジェクトの型 @n ObjectBaseを基底クラスに持っていること
        void CreateObject( Vector2 position = Vector2( 0, 0 ), float angle = PI / 2 ) {
            auto obj = std::make_shared<T>();
            obj->Activate( position, angle );
            objectList.push_back( obj );
            processObjectList.push_back( obj );
        }

        void Update() {
            std::for_each( processObjectList.begin(), processObjectList.end(), []( auto& element ) {
                element.lock()->ReserveStart();
                element.lock()->Update();
            } );

            UpdateObjectList();
        }

        void Draw() {
            std::for_each( processObjectList.begin(), processObjectList.end(), []( auto& element ) {
                element.lock()->Draw();
            } );
        }

        void Finalize() {
            std::for_each( objectList.begin(), objectList.end(), []( auto& element ) {
                element->Finalize();
            } );
        }

       private:
        void UpdateObjectList() {
            // アクティブでないオブジェクトを削除する
            std::erase_if( objectList, []( auto& element ) {
                return !element->IsActive;
            } );

            // 監視対象のオブジェクトがない要素を処理リストから削除
            std::erase_if( processObjectList, []( auto& element ) {
                return element.expired();
            } );
        }

       private:
        std::vector<std::shared_ptr<ObjectBase>> objectList;  // オブジェクト全体
        std::vector<std::weak_ptr<ObjectBase>> processObjectList;  // 処理対象のオブジェクト
    };
}  // namespace shooting::object

#endif  // !OBJECT_MANAGER_H
