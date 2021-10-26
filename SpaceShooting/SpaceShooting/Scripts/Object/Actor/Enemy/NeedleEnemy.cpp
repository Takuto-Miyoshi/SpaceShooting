#include "NeedleEnemy.h"

#include "../../../Definition/StatusLoaderKey.h"
#include "../../../Manager/StatusLoader.h"

namespace shooting::object::enemy {
    void NeedleEnemy::Start() {
        Initialize( status::loaderKey::object::enemy::NEEDLE );

        auto& data { status::StatusLoader::Instance()->Get_a( status::loaderKey::object::enemy::NEEDLE ) };
        bulletIndex = static_cast<uint32_t>( data.ExtraParam1 );
        angle = RandomAngle();
    }

    void NeedleEnemy::Update() {
        EnemyBase::Update();

        Move();
    }

    void NeedleEnemy::Shoot() {
        for ( auto&& i { 0u }; i < bulletIndex; i++ ) {
            ShootTo( Vector2::FromUnit( Vector2::RandomUnit() ) );
        }

        angle = RandomAngle();
    }

    void NeedleEnemy::Move() {
        MoveToForward();
    }
}  // namespace shooting::object::enemy
