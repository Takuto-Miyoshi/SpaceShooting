// 敵の基底クラス

#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../../Definition/ImageDefinition.h"
#include "../../Manager/ImageManager.h"
#include "../ObjectBase.h"

namespace shooting::object {
    class EnemyBase : public ObjectBase {
       public:
        EnemyBase() = default;

        ~EnemyBase() override = default;

       public:
        static void LoadEnemyData() {
            ImageManager::Instance().lock()->LoadGraphHandle( image::enemy );
        }

        void Update() override {
            position.X += sinf( GetNowCount() / 1000.0f );
            position.Y += cosf( GetNowCount() / 1000.0f );
        }

        void Start() override {
            graphicHandle = ImageManager::Instance().lock()->Image( image::enemy.name );
        }

        void Finalize() override {
        }

       private:
    };
}  // namespace shooting::object

#endif  // !ENEMY_BASE_H
