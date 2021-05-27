//includes e bibliotecas
#include "Game.h"


//**MAIN**
int main()
{
    //Inicializando o jogo
    Game game;

    //Game loop
    while (game.getIsWindowOpen())
    {

        //Update
        game.update();

        //Render
        game.render();

    }

    return 0;
}
