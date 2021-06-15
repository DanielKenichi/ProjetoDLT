//includes e bibliotecas
#include "Game.h"


//**MAIN**
int main()
{
    //Inicializando o jogo
    Game game;
    sf::Clock deltaClock;
    
    //Game loop
    while (game.getIsWindowOpen())
    {
        float dt = deltaClock.restart().asSeconds();
        //Update
        game.update(dt);

        //Render
        game.render();
    }

    return 0;
}
