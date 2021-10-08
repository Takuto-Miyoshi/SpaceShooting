#include "StandardBullet.h"

#include "../../Definition/StatusDefinition.h"
#include "../../Definition/StatusLoaderKey.h"

namespace shooting::object {
    void StandardBullet::Start() {
        ObjectBase::Initialize( status::loaderKey::object::bullet::STANDARD );
    }

    void StandardBullet::Move() {
        MoveToForward();
    }
}  // namespace shooting::object
