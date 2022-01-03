
#include <DxLib.h>

#include <Game/Object/Component/Renderer.hpp>
#include <Game/TextureManager.hpp>

namespace game::component {
    void Renderer::Load( std::string_view name ) {
        handle = TextureManager::Instance()->Get( name );
    }

    void Renderer::Load( std::string_view name, std::string_view file ) {
        auto texture { TextureManager::Instance() };
        texture->Load( name, file );
        handle = texture->Get( name );
    }

    void Renderer::Draw( const Transform& transform ) const {
        //DrawRotaGraph( transform.Position->X.Cast<int32_t>(),
        //               transform.Position->Y.Cast<int32_t>(),
        //               1.0,
        //               transform.Angle<double>(),
        //               handle,
        //               true );
        DrawRotaGraph( static_cast<int32_t>( transform.Position.Get().X.Get() ),
                       static_cast<int32_t>( transform.Position.Get().Y.Get() ),
                       1.0,
                       transform.Angle<double>(),
                       handle,
                       true );
    }
}  // namespace game::component
