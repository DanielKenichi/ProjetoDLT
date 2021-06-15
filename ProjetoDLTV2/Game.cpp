#include "Game.h"
#include <stdio.h>

//Variáveis globais
sf::Clock spawnTimer; //timer para spawnar os objetos

// --> Construtor e Inicializadores <--
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
	this->initializeObjects();
	this->initializePlayer();
}

//InitializeVariables() : Inicializa as variáveis iniciais
void Game::initializeVariables()
{
	this->window = nullptr;

	this->objects.initializeQueue();

	this->spawnedObjects.initializeList();

}

//InitializeWindow(): Inicializa a janela com as especificações necessárias
void Game::initializeWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Projeto DLT", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	//this->window->setFramerateLimit(60);

	
	//Carrega e seta a imagem do jogo
	sf::Image icon;
	if(!icon.loadFromFile("resources/icon.png")){ //Imagem quadrada 128x128
		std::cout<<"Falha na leitura do ícone" << std::endl;
	}
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

/*
* *initializeObjects(): Inicializa a fila de objetos a serem gerados e a lista de objetos spawnados
*/
void Game::initializeObjects()
{
	std::srand(time(0));  //inicializando seed aleatoria

	this->generateQueue(10); //definir regra de geração pra queue (etapa de fase)
}

void Game::initializePlayer()
{
	this->player.setPosition(videoMode.width/2, videoMode.height/2);
}

// --> Destrutor <--
Game::~Game()
{
	delete this->window; 
}


//pollEvents(): Verifica eventos (Teclado, Janela aberta)
void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed) //Fecha a janela do jogo ao clicar no "X" da janela
			this->window->close();
		if (this->ev.type == sf::Event::KeyPressed)
		{
			if(ev.key.code == sf::Keyboard::Up){
				player.rotateDirection('u');
			}else if(ev.key.code == sf::Keyboard::Right){
				player.rotateDirection('r');
			}else if(ev.key.code == sf::Keyboard::Down){
				player.rotateDirection('d');
			}else if(ev.key.code == sf::Keyboard::Left){
				player.rotateDirection('l');
			}
		}

	}
}

/*
* update():Atualiza os frames do jogo
*/
void Game::update(float dt)
{
	this->pollEvents();

	this->updateObjects(dt);

	this->testCollisions();

	this->player.updateAll(dt);
}

// updateObjects(): Atualiza as informações dos objetos
void Game::updateObjects(float dt)
{
	sf::Time delay = sf::seconds(0.5f); //delay entre spawns de objetos

	if (spawnTimer.getElapsedTime().asSeconds() >= delay.asSeconds())
	{
		spawnObject();
		spawnTimer.restart(); //restarta o timer de spawn de objetos
	}

	
	if (this->spawnedObjects.getNroElementos() != 0) //se tiver elementos na lista de spawn, os movimenta
	{
		for (int i = 0; i < this->spawnedObjects.getNroElementos(); i++)
		{
			this->spawnedObjects.getObjects()->moveObject(dt);
		}
	}
	

}

/*
* testCollision(): Testa colisões entre obstáculos e o jogador
*/
void Game::testCollisions()
{
	sf::Sprite testObject;
	for (int i = 0; i < this->spawnedObjects.getNroElementos(); i++)
	{
		testObject = this->spawnedObjects.getObjects()->getBody();
		if(player.collidePlayer(testObject)) // Colisão com player
		{
			//Remover objeto i
			std::cout << "Player Acertado por Objeto " << i << std::endl;
			//Perda de vida ocorre no próprio objeto
		} else if(player.collideShields(testObject)) // Colisão com escudos
		{
			//Remover objeto i 
			std::cout << "Escudo Acertado por Objeto " << i << std::endl;
			//Aumentar a pontuação (TODO:)
		}
	}
}

/*
* render(): Renderiza os objetos do jogo
*/
void Game::render()
{
	this->window->clear(sf::Color(19, 22, 28)); //limpa o frame antigo

	this->player.renderAll(this->window); //Desenha o Player

	this->renderObjects();

	this->window->display(); //Exibe na tela o desenho realizado no frame

}

//renderObjects(): Desenha os inimigos na tela
void Game::renderObjects()
{
	for (int i = 0; i < this->spawnedObjects.getNroElementos(); i++)
	{
		(this->window)->draw(this->spawnedObjects.getObjects()->getBody());
	}
	
}

/*
* generateQueue(int size): Gera a fila de objetos de acordo com um parâmetro decidido no inicio de cada fase
*/
void Game::generateQueue(int size)
{
	for (int i = 0; i < size; i++)
	{
		this->objects.newObject();
	}
}

/*
* spawnObject(): Checa se existem objetos a serem spawnados, e se houver, o coloca na lista de spawn
*/
void Game::spawnObject()
{
	if (this->objects.isEmpty() == false)
	{
		Object object = this->objects.removeObject();
		this->spawnedObjects.newObject(&object);
	}
}

//**Getters**
//getIsWindowOpen(): Retorna true caso a janela do jogo esteja aberta, e false caso contrário
const bool Game::getIsWindowOpen()
{
	return this->window->isOpen();
}