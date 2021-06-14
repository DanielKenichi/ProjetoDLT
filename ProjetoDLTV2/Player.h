#ifndef PLAYER_H
#define PLAYER_H

/*
* A classe do jogador 
*/

//Bibliotecas e includes
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player : public sf::Transformable
{
public:
    Player();
    ~Player();

    // HP
    int getHP();
    // Inicializa os Escudos
    void InitializeShields(bool top, bool bottom, bool left, bool right); 
    // Rotaciona o player em uma direção
    void rotateDirection(char dir); // Usa rotacionar para as 4 direções "t","r","b","l"
    // Get Player Rotation
    double getPRotation();
private:

    // Vida
    int HP;

    // Escudos (4, alguns desabilitados)
    sf::Sprite sTop;
    sf::Sprite sBottom;
    sf::Sprite sLeft;
    sf::Sprite sRight;

    // Sprite e funções relacionadas
    sf::Sprite spr; // Player
    void rotatePlayer(double ang); // Rotacionar
};

#endif // !PLAYER_H