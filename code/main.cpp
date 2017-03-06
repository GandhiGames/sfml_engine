
#include "Game.hpp"

int main(int, char const**)
{
    Game game;
    
    while (!game.GetWindow()->IsDone()) {
        game.Update();
        game.Render();
        game.LateUpdate();
    }
    
    return EXIT_SUCCESS;
}
