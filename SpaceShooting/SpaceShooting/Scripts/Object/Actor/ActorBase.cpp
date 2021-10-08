#include "ActorBase.h"

#include "../../Manager/StatusLoader.h"

namespace shooting::object {
    void ActorBase::Update() {
        UpdateStatus();
    }

    void ActorBase::Draw() const {
        ObjectBase::Draw();

        // HPを表示
        DrawString( static_cast<int32_t>( position.X - camera.lock()->Position->X ),
                    static_cast<int32_t>( position.Y - camera.lock()->Position->Y ),
                    ( "HP:" + std::to_string( static_cast<double>( actorStatus.Hp ) ) + "/" + std::to_string( static_cast<double>( actorStatus.MaxHp ) ) ).c_str(),
                    GetColor( 255, 255, 255 ) );
        // レベルを表示
        DrawString( static_cast<int32_t>( position.X - camera.lock()->Position->X ),
                    static_cast<int32_t>( position.Y - camera.lock()->Position->Y - 30 ),
                    ( "LEVEL:" + std::to_string( level ) ).c_str(),
                    GetColor( 255, 255, 255 ) );
    }

    void ActorBase::Initialize( const std::string& objectName ) {
        ObjectBase::Initialize( objectName );

        auto& data = status::StatusLoader::Instance()->Get_a( objectName );
        actorStatusBase = data.ActorData;
        actorStatus = actorStatusBase;
    }

    void ActorBase::UpdateStatus() {
        objectStatus = objectStatusBase;
        actorStatus.MaxHp = actorStatusBase.MaxHp;
        actorStatus.Speed = actorStatusBase.Speed;
    }

    void ActorBase::LevelUp() {
        actorStatusBase.LevelUp();
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
