#include "EnemyBase.h"

namespace shooting::object {
    void EnemyBase::LoadEnemyData() {
        ImageManager::Instance()->LoadGraphHandle( image::ENEMY );
    }

    void EnemyBase::Start() {
        graphicHandle = ImageManager::Instance()->Image( image::ENEMY.name );
        collisionRadius = status::enemy::COLLISION_RADIUS;
    }

    void EnemyBase::Update() {
    }

    void EnemyBase::Collide() {
    }
}  // namespace shooting::object
