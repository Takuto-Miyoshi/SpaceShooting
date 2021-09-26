#include "ActorBase.h"

namespace shooting::object {
    void ActorBase::Draw() const {
        ObjectBase::Draw();

        // HPを表示
        DrawString( static_cast<int32_t>( position.X - camera.lock()->Position->X ),
                    static_cast<int32_t>( position.Y - camera.lock()->Position->Y ),
                    ( std::to_string( static_cast<int32_t>( actorStatus.Hp ) ) + "/" + std::to_string( static_cast<int32_t>( actorStatus.MaxHp ) ) ).c_str(),
                    GetColor( 255, 255, 255 ) );
    }

    void ActorBase::MoveToForward() {
        ObjectBase::MoveToForward( actorStatus.Speed );
    }

    void ActorBase::MoveTo( const Vector2& direction ) {
        ObjectBase::MoveTo( direction, actorStatus.Speed );
    }

    auto ActorBase::AttackPower() const -> double {
        return 0.0;
    }

    auto ActorBase::TakeDamage( const double& attackPower ) -> bool {
        actorStatus.Hp -= attackPower;

        return actorStatus.Hp <= 0;
    }
}  // namespace shooting::object
