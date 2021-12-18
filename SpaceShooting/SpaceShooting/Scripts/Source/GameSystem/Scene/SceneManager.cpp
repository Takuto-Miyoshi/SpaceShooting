
#include <Game/Exception.hpp>
#include <Game/SceneManager.hpp>
#include <format>

namespace game {
    void SceneManager::ChangeScene( const std::string& name ) {
        try {
            const auto next { sceneList.find( name ) };
            if ( next == sceneList.end() ) {
                throw exception::NotFound( std::format( "{} はシーンリストに登録されていません。", name ) );
            }

            if ( currentScene ) [[likely]] { currentScene->Finalize(); }

            currentScene = next->second;
            currentScene->Initialize();
        }
        catch ( const std::exception& ) {
            return;
        }
    }

    void SceneManager::Update() {
        if ( currentScene ) {
            currentScene->Update();
            currentScene->Draw();
        }
    }
}  // namespace game
