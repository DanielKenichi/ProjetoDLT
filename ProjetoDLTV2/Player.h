#ifndef PLAYER_H
#define PLAYER_H

/*
* A classe do jogador 
*/

//Bibliotecas e includes
#include <iostream>
#include "Collision.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player : public sf::Transformable{
public:
    Player();
    ~Player();

    // HP
    int getHP();
    void setHP(int hp);
    // Inicializa os Escudos
    void InitializeShields(bool top, bool bottom, bool left, bool right); 
    // Rotaciona o player em uma direção
    void rotateDirection(char dir, float dt); // Usa rotacionar para as 4 direções "u","r","d","l"
    // Get Player Rotation
    double getPRotation();

    // Renderização e Update
    void updateAll(float dt);
    void renderAll(sf::RenderWindow *win);

    // Testa Colisão
    bool collideShields(sf::Sprite obj);
    bool collidePlayer(sf::Sprite obj);
 
private:

    // Vida
    int HP;
    // Velocidade, Aceleração
    double velocidade = 0;
    double angAlvo = 0;
    const double ACELERACAO = 10;
    //const double ACELERACAO = 1;
    const double DESACELERACAO = 1;
    const double VELOCIDADEMAX = 100;
    //const double VELOCIDADEMAX = 10;

    // Escudos (4, alguns desabilitados)
    sf::Sprite sTop;
    sf::Sprite sDown;
    sf::Sprite sLeft;
    sf::Sprite sRight;
    // Animação Escudos
    sf::Clock cTop;

    // Sprite e funções relacionadas
    sf::Sprite spr; // Player
    void rotatePlayer(double ang, float dt); // Rotacionar
    // Animação Player
    sf::Clock cSpr;

    // Texturas
    sf::Texture tPlayer;
    sf::Texture tShield;
    void initializeSprites();
};

#endif // !PLAYER_H