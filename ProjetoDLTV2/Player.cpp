#include "Player.h"
#include <stdio.h>

Player::Player()
{
    std::cout << "Player Criado" << std::endl;
}

Player::~Player()
{
    std::cout << "Player Destruído" << std::endl;
}

int Player::getHP(){
    return HP;
}

void Player::rotateDirection(char dir){
    switch(dir){
        case 't':
            this->rotatePlayer(0.f);
        break;
        case 'r':
            this->rotatePlayer(90.f);
        break;
        case 'b':
            this->rotatePlayer(180.f);
        break;
        case 'l':
            this->rotatePlayer(270.f);
        break;
    }
}

void Player::rotatePlayer(double ang)
{
    std::cout << "Rotacionando para " << ang << "º graus" << std::endl;
    //this->spr.setRotation(ang);
    this->setRotation(ang);
    //TODO: testar se só isso já rotaciona tudo? Ou fazer tudo pela rotação do sprite, como atualizar os escudos
    //TODO: Smoothing
}

double Player::getPRotation(){
    return this->spr.getRotation();
}

void InitializeShields(bool top, bool right, bool bottom, bool left){
    // Inicializar os sprites (procurar nos resources)
    if(top){

    }
    if(right){

    }
    if(bottom){

    }
    if(left){

    }
    //Configurar offset de rotação -> entity.setOrigin(10.f, 20.f); (Padrão é 0, 0)
    //Setar a rotação offset de cada escudo -> entity.setRotation(x); com x = 0, 90, 180, 270
}