#include "TransBullet.h"

#include "../../Manager/BulletFactory.h"

namespace shooting::object {
    void TransBullet::Initialize( BulletBase* transTarget, const status::bullet::TransData& transData ) noexcept {
        target = transTarget;
        next = transData;

        interval = next.TimeToTrans;
    }

    void TransBullet::Stack( const status::bullet::TransData& stackData ) {
        transStack.push( stackData );
    }

    void TransBullet::Update() noexcept {
        isActive = target->IsActive;
    }

    void TransBullet::Trans() {
        target->IsActive = false;
        target = BulletFactory::Instance()->Create( target->Kind, target->Position, target->Angle, next.ToBulletData );

        if ( transStack.empty() ) {
            isActive = false;
            return;
        }

        next = transStack.front();
        transStack.pop();
    }
}  // namespace shooting::object
