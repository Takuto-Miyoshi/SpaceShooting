#include "ObjectBase.h"

namespace shooting::object {
    void ObjectBase::Activate( const status::ObjectKind& objectKind, const Vector2& resetPosition, const float& resetAngle ) {
        kind = objectKind;
        position = resetPosition;
        angle = resetAngle;
        isActive = true;
    }
}  // namespace shooting::object
