#include "ObjectManager.h"

#include "../Definition/StatusDefinition.h"

namespace shooting::object {
    void ObjectManager::Initialize() {
        objectList.reserve( OBJECT_CAPACITY );
    }

    void ObjectManager::Update() {
        for ( auto&& obj : std::as_const( objectList ) ) {
            obj->ReserveStart();
            obj->Update();
        }

        /*
            当たり判定
        */

        EraseUnactiveObject();
    }

    void ObjectManager::Draw() {
        for ( auto&& obj : std::as_const( objectList ) ) {
            obj->Draw();
        }
    }

    void ObjectManager::Finalize() {
        objectList.clear();
    }

    void ObjectManager::EraseUnactiveObject() {
        std::erase_if( objectList, []( auto& element ) {
            return !element->IsActive;
        } );
    }
}  // namespace shooting::object
