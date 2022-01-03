
#include <DxLib.h>

#include <Game/Object/ObjectBase.hpp>
#include <Game/TextureManager.hpp>

namespace game {
    void ObjectBase::Initialize() {
        SetDefault();

        renderer.Load( object.TextureName, object.TexturePath );
    }

    void ObjectBase::Exec() {
    }

    void ObjectBase::Draw() const {
        renderer.Draw( transform );
    }
}  // namespace game
