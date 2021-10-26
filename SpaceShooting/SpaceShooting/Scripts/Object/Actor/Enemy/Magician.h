#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "EnemyBase.h"

namespace shooting::object {
    class Magician : public EnemyBase {
       public:
        Magician() = default;

        ~Magician() override = default;

       public:
        void Update() override;

       protected:
        void Start() override;

        void Shoot() override;

       private:
        void Warp();

       private:
        double shootDistance { 0.0 };  // 発射する弾の距離

        uint32_t bulletIndex { 0 };  // 一周の弾数
        uint32_t progress { 0 };  // 進行度

        double toPlayerDistance { 0.0 };  // ワープ時のプレイヤーとの距離

        double transTime { 0.0 };  // Transformまでの時間
    };
}  // namespace shooting::object

#endif  // !MAGICIAN_H
