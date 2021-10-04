#include "StandardEnemy.h"

#include "../../../Manager/BulletFactory.h"
#include "../../../Manager/ObjectManager.h"

namespace shooting::object {
    void StandardEnemy::Start() {
        Initialize( image::STANDARD_ENEMY.name,
                    status::enemy::StandardEnemy::OBJECT,
                    status::enemy::StandardEnemy::ACTOR,
                    status::enemy::StandardEnemy::ENEMY.Exp,
                    status::enemy::StandardEnemy::BULLET );
    }

    void StandardEnemy::Update() {
        EnemyBase::Update();

        Shoot();
        Move();
    }

    void StandardEnemy::Move() {
        angle += timeManager.lock()->DeltaTime;
        MoveToForward();
    }

    void StandardEnemy::Shoot() {
        shotCount += timeManager.lock()->DeltaTime;
        if ( shotCount >= status::enemy::StandardEnemy::SHOT_INTERVAL ) {
            shotCount = 0;

            float target = position.AngleTo( ObjectManager::Instance()->PlayerPosition() );
            ShootTo( target );
        }
    }
}  // namespace shooting::object
