#include "Game.hpp"

//TODO(robert): Rename this file to Win32
//TODO(robert): Move cfg files to media folder - edit build file
int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR     lpCmdLine,
  int       nCmdShow
)
{
    Game game;
    
    while (!game.GetWindow()->IsDone()) {
        game.Update();
        game.Render();
        game.LateUpdate();
    }
    
    return EXIT_SUCCESS;
}
