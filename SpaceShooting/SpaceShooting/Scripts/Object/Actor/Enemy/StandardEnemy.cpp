#include "StandardEnemy.h"

#include "../../../Definition/StatusLoaderKey.h"
#include "../../../Manager/BulletFactory.h"
#include "../../../Manager/ObjectManager.h"

namespace shooting::object {
    void StandardEnemy::Start() {
        Initialize( status::loaderKey::object::enemy::STANDARD );
    }

    void StandardEnemy::Update() {
        EnemyBase::Update();

        Move();
    }

    void StandardEnemy::Move() {
        angle += timeManager.lock()->DeltaTime.Cast<float>();
        MoveToForward();
    }

    void StandardEnemy::Shoot() {
        ShootTo( position.AngleTo<float>( ObjectManager::Instance()->PlayerPosition() ) );
    }
}  // namespace shooting::object
