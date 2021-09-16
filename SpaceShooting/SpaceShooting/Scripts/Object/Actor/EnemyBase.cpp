#include "EnemyBase.h"

namespace shooting::object {
    void EnemyBase::LoadEnemyData() {
        ImageManager::Instance()->LoadGraphHandle( image::ENEMY );
    }
}  // namespace shooting::object
