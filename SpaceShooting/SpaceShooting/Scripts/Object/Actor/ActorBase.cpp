#include "ActorBase.h"

#include "../../Manager/StatusLoader.h"

namespace shooting::object {
    void ActorBase::Update() {
        UpdateStatus();
    }

    void ActorBase::Draw() const {
        ObjectBase::Draw();

        // HPを表示
        DrawStringOnHead( "HP:" + std::to_string( actorStatus.Hp ) + "/" + std::to_string( actorStatus.MaxHp ) );

        // レベルを表示
        DrawStringOnHead( "LEVEL:" + std::to_string( level ), -30.0 );
    }

    void ActorBase::Initialize( const std::string& objectName ) {
        ObjectBase::Initialize( objectName );

        auto& data { status::StatusLoader::Instance()->Get_a( objectName ) };
        actorStatusBase = data.ActorData;
        actorStatus = actorStatusBase;
    }

    void ActorBase::UpdateStatus() noexcept {
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

    void ActorBase::MoveTo( const Vector2<double>& direction ) {
        ObjectBase::MoveTo( direction, actorStatus.Speed );
    }

    auto ActorBase::AttackPower() const noexcept -> double {
        return 0.0;
    }

    auto ActorBase::TakeDamage( const double& attackPower ) noexcept -> bool {
        actorStatus.Hp -= attackPower;

        return actorStatus.Hp <= 0;
    }
}  // namespace shooting::object
