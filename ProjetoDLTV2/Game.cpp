#include "Game.h"
#include <stdio.h>

//**Construtores e destrutores**
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
	this->initializeObjects();
}

Game::~Game()
{
	delete this->window; 
}

//**Getters**

//getIsWindowOpen(): Retorna true caso a janela do jogo esteja aberta, e false caso contrário
const bool Game::getIsWindowOpen()
{
	return this->window->isOpen();
}


//**Métodos Públicos**

//update():Atualiza os frames do jogo
void Game::update()
{
	this->pollEvents();
	
	this->updateObjects();
}

//render(): Renderiza os objetos do jogo
void Game::render()
{
	this->window->clear(sf::Color(19, 22, 28)); //limpa o frame antigo

	this->renderObjects();

	this->window->display(); //Exibe na tela o desenho realizado no frame

}


//**Métodos Privados**

//InitializeVariables() : Inicializa as variáveis iniciais
void Game::initializeVariables()
{
	this->window = nullptr;
}

//InitializeWindow(): Inicializa a janela com as especificações necessárias
void Game::initializeWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Projeto DLT", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	this->window->setFramerateLimit(60);

	
	//Carrega e seta a imagem do jogo
	sf::Image icon;
	if(!icon.loadFromFile("resources/icon.png")){ //Imagem quadrada 128x128
		std::cout<<"Falha na leitura do ícone" << std::endl;
	}
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
/*
* pollEvents(): Verifica se a janela está aberta 
*/
void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed) //Fecha a janela do jogo ao clicar no "X" da janela
			this->window->close();
	}
}

/*
* *initializeObjects(): Inicializa a fila de objetos a serem gerados e a lista de objetos spawnados
*/
void Game::initializeObjects()
{
	this->objects.initializeQueue();

	this->spawnedObjects.initializeList();

	this->objects.newObject();
	
}
/*
* renderEnemies(): Desenha os inimigos na tela
*/
void Game::renderObjects()
{
	(this->window)->draw(this->spawnedObjects.getObjects().getBody());
}
/*
* updateObjects(): Atualiza as informações dos objetos
*/
void Game::updateObjects()
{
	sf::Vector2f pos;
	if (this->objects.isEmpty() == false)
	{
		Object object = this->objects.removeObject();
		this->spawnedObjects.newObject(&object);
	}
	
	this->spawnedObjects.getObjects().moveObject();

	/*debug*
	pos = this->spawnedObjects.getObjects().getBody().getPosition();

	std::cout << pos.x << pos.y << std::endl;*/
}



