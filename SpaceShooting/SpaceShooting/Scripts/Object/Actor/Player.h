// プレイヤーの挙動

#ifndef PLAYER_H
#define PLAYER_H

#include "../../Definition/InputDefinition.h"
#include "../ObjectBase.h"

namespace shooting::object::actor {
    class Player : public ObjectBase {
       public:
        Player() = default;

        ~Player() override = default;

       public:
        void Update() override;

        void Finalize() override;

       protected:
        void Start() override;

       private:
        void MoveLeft( InputState inputState );

        void MoveRight( InputState inputState );

        void MoveUp( InputState inputState );

        void MoveDown( InputState inputState );

        void Shoot( InputState inputState );

        void LookToCursor();

       private:
    };
}  // namespace shooting::object::actor

#endif  // !PLAYER_H
