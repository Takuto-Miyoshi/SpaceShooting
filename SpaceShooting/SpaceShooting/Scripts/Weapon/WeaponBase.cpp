#include "WeaponBase.h"

#include "../Manager/BulletFactory.h"
#include "../Manager/StatusLoader.h"
#include "../Manager/TimeManager.h"

namespace shooting::weapon {
    void WeaponBase::Initialize( const object::ActorBase& user, const uint8_t& useRarity ) {
        position = &*user.Position;
        angle = &*user.Angle;
        level = &*user.Level;
        kind = ConvertKind( user.Kind );
        rarity = useRarity;
    }

    void WeaponBase::Update() {
        UpdateBulletStatus();

        timer -= TimeManager::Instance()->DeltaTime;
        if ( timer <= 0 ) {
            shootable = true;
        }
    }

    void WeaponBase::Shoot() {
        if ( shootable == false ) [[likely]] { return; }
        ShootProcess();
        ShootedProcess();
    }

    void WeaponBase::ShootedProcess() noexcept {
        shootable = false;
        timer = weaponStatus.Interval;
    }

    void WeaponBase::InitializeWeapon( const std::string& objectName ) {
        auto& data { object::status::StatusLoader::Instance()->Get_a( objectName, rarity ) };

        weaponStatus = data.WeaponData;
        baseBulletData = data.BulletData;
        bulletStatus = baseBulletData;
    }

    void WeaponBase::UpdateBulletStatus() noexcept {
        // 初期レベルは1なので99.0+1=100%
        bulletStatus.AttackPower = PercentOf( baseBulletData.AttackPower, ( 99.0 + pow( *level, 2 ) ) );
    }

    auto WeaponBase::ShootForward() -> object::BulletBase* {
        return ShootTo( *position, *angle );
    }

    auto WeaponBase::ShootTo( const Vector2<double>& shootPosition ) -> object::BulletBase* {
        return ShootTo( shootPosition, *angle );
    }

    auto WeaponBase::ShootTo( const float& shootAngle ) -> object::BulletBase* {
        return ShootTo( *position, shootAngle );
    }

    auto WeaponBase::ShootTo( const Vector2<double>& shootPosition, const float& shootAngle ) -> object::BulletBase* {
        return object::BulletFactory::Instance()->Create( kind, shootPosition, shootAngle, bulletStatus );
    }

    auto WeaponBase::ConvertKind( const object::status::ObjectKind& source ) const noexcept -> object::status::ObjectKind {
        switch ( source ) {
            case object::status::ObjectKind::Enemy: return object::status::ObjectKind::EnemyBullet;
            case object::status::ObjectKind::Player: return object::status::ObjectKind::PlayerBullet;
            default: return source;
        }
    }
}  // namespace shooting::weapon
