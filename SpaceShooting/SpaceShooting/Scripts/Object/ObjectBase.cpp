#include "ObjectBase.h"

namespace shooting::object {
    void ObjectBase::Activate( const Vector2& resetPosition, const float& resetAngle ) {
        position = resetPosition;
        angle = resetAngle;
        isActive = true;
    }
}  // namespace shooting::object
