#include "TransBullet.h"

#include "../../Manager/BulletFactory.h"

namespace shooting::object {
    void TransBullet::Initialize( BulletBase* transTarget, const status::bullet::TransData& transData ) {
        target = transTarget;
        next = transData;
    }

    void TransBullet::Stack( const status::bullet::TransData& stackData ) {
        transStack.push( stackData );
    }

    void TransBullet::Update() {
        // すでに0以下なら次の時間を設定
        if ( transTime <= 0 ) { transTime = next.TimeToTrans; }

        transTime -= timeManager.lock()->DeltaTime;

        if ( transTime <= 0 ) {
            target->IsActive = false;
            target = BulletFactory::Instance()->Create( target->Kind, target->Position, target->Angle, next.ToBulletData );

            if ( transStack.empty() ) {
                isActive = false;
                return;
            }

            next = transStack.front();
            transStack.pop();
        }

        isActive = target->IsActive;
    }
}  // namespace shooting::object
