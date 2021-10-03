#include "EnemyBase.h"

namespace shooting::object {
    void EnemyBase::LoadEnemyData() {
        ImageManager::Instance()->LoadGraphHandle( image::STANDARD_ENEMY );
        ImageManager::Instance()->LoadGraphHandle( image::EXPLODE_ENEMY );
    }
}  // namespace shooting::object
