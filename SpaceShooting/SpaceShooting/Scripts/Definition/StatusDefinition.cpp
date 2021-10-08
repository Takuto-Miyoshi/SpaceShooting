#include "StatusDefinition.h"

namespace shooting::object {
    // --------- Object ----------

    const uint32_t ObjectSetting::OBJECT_CAPACITY { 500 };
    const double ObjectSetting::VALID_DISTANCE { 1000.0 };
    const double ObjectSetting::SPAWN_INTERVAL { 5.0 };
    const uint32_t ObjectSetting::MAX_LEVEL { 100 };

    // --------------------------
    // --------- Lottery ----------

    const uint32_t Lottery::BOX_CAPACITY { 10 };

    // --------------------------

    namespace status {
        auto Grow::Dest() -> double {
            auto value = Fixed + RandomReal( Fluctuation );
            return PercentOf( value, UseRatio );
        }

        void Actor::LevelUp() {
            auto increaseHp = GrowHp.Dest();
            MaxHp += increaseHp;
            Hp += increaseHp;
        }

        void Bullet::LevelUp() {
            AttackPower += GrowAttackPower.Dest();
        }

        const double BulletSetting::LIFE_SPAN_OF_BULLET { 5.0 };

        const double ExperienceSetting::RATE_OF_LEVEL_TO_EXP { 5.0 };
        const double ExperienceSetting::RATE_OF_NEXT_LEVEL { 39.1 };
        const int32_t ExperienceSetting::MULTIPLE_OF_NEXT_LEVEL { 3 };

        // --------------------------

    }  // namespace status
}  // namespace shooting::object
