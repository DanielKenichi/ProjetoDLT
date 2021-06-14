#include "Player.h"
#include <stdio.h>

Player::Player()
{
    // Carregamento de Texturas
    if(!tPlayer.loadFromFile("resources/Player.png")){ //Imagem quadrada 128x128
		std::cout<<"Player.cpp : Falha na leitura de Player.png" << std::endl;
	}
    tPlayer.setSmooth(true);
    if(!tShield.loadFromFile("resources/Escudo.png")){ //Imagem quadrada 128x128
		std::cout<<"Player.cpp : Falha na leitura de Escudo.png" << std::endl;
	}
    tShield.setSmooth(true);

    // Atribuição de Texturas aos Sprites
    spr.setTexture(tPlayer);
    sTop.setTexture(tShield);
    sRight.setTexture(tShield);
    sBottom.setTexture(tShield);
    sLeft.setTexture(tShield);

    // Ajuste de Tamanho
    const sf::Vector2f spriteScale(0.5f, 0.5f);
    spr.setScale(spriteScale);
    sTop.setScale(spriteScale);
    sRight.setScale(spriteScale);
    sBottom.setScale(spriteScale);
    sLeft.setScale(spriteScale);

    // Ajuste de Origem
    sf::Vector2f middle(spr.getLocalBounds().width/2, spr.getLocalBounds().height/2);
    spr.setOrigin(middle);
    sTop.setOrigin(middle + sf::Vector2f(0.0f, middle.y));
}

Player::~Player()
{
    std::cout << "Player Destruido" << std::endl;
}

int Player::getHP()
{
    return HP;
}

void Player::rotateDirection(char dir)
{
    switch(dir){
        case 'u': //up
            this->rotatePlayer(0.f);
        break;
        case 'r': //right
            this->rotatePlayer(90.f);
        break;
        case 'd': //down
            this->rotatePlayer(180.f);
        break;
        case 'l': //left
            this->rotatePlayer(270.f);
        break;
    }
}

void Player::rotatePlayer(double ang)
{
    std::cout << "Rotacionando para " << ang << "o graus" << std::endl;
    //this->spr.setRotation(ang);
    this->setRotation(ang);
    //TODO: Smoothing
}

double Player::getPRotation()
{
    return this->spr.getRotation();
}

void InitializeShields(bool top, bool right, bool bottom, bool left)
{
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

void Player::renderAll(sf::RenderWindow *win)
{
    win->draw(spr);
    win->draw(sTop);
}

void Player::updateAll(float dt)
{
    //Temporário FIXME: solução permanente para todas as atualizações
    spr.setPosition(this->getPosition());
    sTop.setPosition(this->getPosition());
    spr.setRotation(this->getRotation());
    sTop.setRotation(this->getRotation());
}