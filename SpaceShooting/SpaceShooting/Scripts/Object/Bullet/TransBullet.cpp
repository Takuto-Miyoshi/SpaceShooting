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
        if ( transTime <= 0 ) { transTime = next.TimeToTrans; }
        transTime -= timeManager.lock()->DeltaTime;
        if ( transTime <= 0 ) {
            target->IsActive = false;
            target = BulletFactory::Instance()->Create( target->Kind, next.TransTo, target->Position, target->Angle, next.ToBulletData );

            if ( transStack.empty() ) {
                isActive = false;
                return;
            }
            next = transStack.front();
            transStack.pop();
        }

        isActive = target->IsActive;
    }

    void TransBullet::Draw() const {
    }

    void TransBullet::Start() {
    }

    auto TransBullet::AttackPower() const -> double {
        return 0.0;
    }

    auto TransBullet::TakeDamage( const double& attackPower ) -> bool {
        return false;
    }
}  // namespace shooting::object
