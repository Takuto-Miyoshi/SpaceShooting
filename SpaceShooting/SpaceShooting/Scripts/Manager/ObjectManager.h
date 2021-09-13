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
        }

        template<class T>
        /// @brief オブジェクトを作成
        /// @tparam T 作成するオブジェクトの型 @n ObjectBaseを基底クラスに持っていること
        auto CreateObject() -> std::weak_ptr<T> {
            auto obj = std::make_shared<T>();
            objectList.push_back( obj );
            return obj;
        }

        void Update() {
            std::for_each( objectList.begin(), objectList.end(), []( auto& element ) {
                element->ReserveStart();
                element->Update();
            } );
        }

        void Draw() {
            std::for_each( objectList.begin(), objectList.end(), []( auto& element ) {
                element->Draw();
            } );
        }

        void Finalize() {
            std::for_each( objectList.begin(), objectList.end(), []( auto& element ) {
                element->Finalize();
            } );
        }

       private:
        std::vector<std::shared_ptr<ObjectBase>> objectList;
    };
}  // namespace shooting::object

#endif  // !OBJECT_MANAGER_H
