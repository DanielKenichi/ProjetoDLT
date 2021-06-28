#include "Game.h"
#include <stdio.h>
#include <String>
#include <math.h>

// --> Construtor e Inicializadores <--
Game::Game(){
	initializeVariables();
	initializeWindow();
	initializeTexts();
}
// --> Destrutor <--
Game::~Game(){
	delete window;
}

/*
* update():Atualiza os frames do jogo de acordo com cada estado:
*	State 0: Main Screen 
*	State 1: Gerando nova fase
*   State 2: Em jogo
*   State 3: Game over
*	State 4: Pause
*/
void Game::update(float dt){

	pollEvents(dt);

	//state 0
	if (state == 0){
		//std::cout << "Estou na tela principal" << std::endl;


		//condição de saida : start game
		if (start == true){
			initializePlayer();
			player.setHP(3);
			score = 0;
			state = 1;
		}
		
	}
	//state 1
	if (state == 1){
		std::cout << "gerando objetos da fase: " << level <<  std::endl;
		this->pass = false;
		initializeObjects(dt);

		LastObjTimer = objects.getFirst().getHitTime(); //Timers para tratamento de colisao
		checkerTimer = sf::seconds(-999.f);

		if (isPlaying == false) { //toca a musica
			musica.play();
			isPlaying = true;
		}
			

		if (level % 5 == 0){ //incrementa vida do player a cada 5 níveis
			player.setHP(player.getHP() + 1);
			player.playNewLive();
		} 

		//condição de saída: ter gerado os objetos
		state = 2;
	}

	//State 2
	if (state == 2){

		hp = player.getHP();
		updateObjects(dt);
		testCollisions();
		player.updateAll(dt);
		
		if (player.getHP() == 1) { //musica mais rapida caso player esteja quase morto
			musica.setPitch(1.2f);
		}
		else {
			musica.setPitch(1.f);
		}

		//condições de saída: Zerar hp 
		if (player.getHP() == 0){
			musica.stop();
			isPlaying = false;
			state = 3;
		}

		//Passar a fase
		else if (pass == true){
			std::cout << "YAY passou" << std::endl;
			level++;
			inGame = false;
			state = 1;
		}
		//Pausar o jogo
		else if (pause == true) {
			musica.pause();
			state = 4;
		}
	}

	//State 3
	if (state == 3) {
		//std::cout << "Game Over" << std::endl;
		//esvaziando lista e fila
		while (objects.isEmpty() == false) {
			objects.removeObject();
		}
		while (spawnedObjects.getNroElementos() != 0) {
			spawnedObjects.removeObject();
		}

		hp = player.getHP();
		player.updateAll(dt);

		//voltando variaveis ao estado inicial
		inGame = false;
		level = 1;
		spawnTimer = sf::seconds(0.f);
		
		

		//condição de saida: Após confirmação do player, voltar para tela inicial
		if (start == false) {
			state = 0;
		}		
	}

	//state 4
	if (state == 4) {
		//std::cout << "Jogo pausado" << std::endl;
		//Condição de Saída: Despausar o jogo
		if (pause == false) {
			musica.play();
			state = 2;
		}
	}
	
}

/*
* render(): Renderiza os objetos do jogo
* 	State 0: Main Screen 
*	State 1: Gerando nova fase
*   State 2: Em jogo
*   State 3: Game over
*	State 4: Pause
*/
void Game::render(){

	/*sf::View view;
	sf::FloatRect;*/

	//state 0 
	if (state == 0){ //renderiza mainScreen
		sf::RectangleShape opaco(sf::Vector2f(videoMode.width, videoMode.height));

		window->clear(sf::Color(19, 22, 28)); //limpa o frame antigo
		window->draw(background);
		
		opaco.setFillColor(sf::Color(0,0,0,150));
		window->draw(opaco);
		renderInicial();
	}
	
	//state 1
	if (state == 1){}

	//state 2
	if (state == 2){ //renderiza a fase, objetos o jogador e as pontuações
		window->clear(sf::Color(19, 22, 28)); //limpa o frame antigo

		window->draw(background);

		player.renderAll(window);

		renderObjects();

		renderScore();
	}

	//state 3
	if (state == 3) {//renderiza tela de Game over
		sf::RectangleShape opaco(sf::Vector2f(videoMode.width, videoMode.height));

		window->clear(sf::Color(19, 22, 28)); //limpa o frame antigo
		
		window->draw(background);

		player.renderAll(window); //Desenha o Player

		renderObjects();

		opaco.setFillColor(sf::Color(0,0,0,150));
		window->draw(opaco);

		renderGameOver();
	}

	//state 4
	if (state == 4){ //renderiza tela de pause
		sf::RectangleShape opaco(sf::Vector2f(videoMode.width, videoMode.height));
		opaco.setFillColor(sf::Color(0,0,0,150));

		window->draw(background);

		player.renderAll(window); //Desenha o Player

		renderScore();

		renderObjects();

		window->draw(opaco);
		renderPause();
	}

	window->display(); //Exibe na tela o desenho realizado no frame
}


//**Getters**
//getIsWindowOpen(): Retorna true caso a janela do jogo esteja aberta, e false caso contrário
const bool Game::getIsWindowOpen(){
	return window->isOpen();
}

//**Outros metodos**

//InitializeVariables() : Inicializa as variáveis iniciais
void Game::initializeVariables(){
	window = nullptr;

	start = false;
	pause = false;
	isPlaying = false;

	spawnTimer = sf::seconds(0.f);
	checkerTimer = sf::seconds(-999.f);
	state = 0; 
	level = 1;
	pass = false;
	inGame = false;

	objects.initializeQueue();
	spawnedObjects.initializeList();

	if (!musica.openFromFile("resources/Musics/ES_Glitching Through the Sky - William Benckert.wav"))
		std::cout << "Falha ao carregar a música de fundo" << std::endl;

	musica.setLoop(true);
	musica.setVolume(20.f);

	if (!tBackground.loadFromFile("resources/cenarioimprovisado.png"))
		std::cout << "Failed loading background image" << std::endl;

	background.setTexture(tBackground);

	if(!font.loadFromFile("resources/Fonts/Rubik.ttf")){
		std::cout << "Falha no carregamento da fonte" << std::endl;
	}

}

/*
sf::Vector2f round(const sf::Vector2f vector){
    return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}*/

/*
* initializeTexts(): Inicializa os textos a serem escritos no jogo
*/
void Game::initializeTexts(){

	// Texto HP
	tHP = sf::Text{"HP: ", font, 32};
	tHP.setPosition(10,0);

	// Texto Score
	tScore = sf::Text{"Score: ", font, 32};
	tScore.setPosition(10, tHP.getCharacterSize() + 10);

	// Texto Level
	nivel = sf::Text{ "Level ", font, 32 };
	nivel.setPosition(10, nivel.getCharacterSize() + 52);

	// Texto Gameover
	tGameover = sf::Text{"Gameover", font, 128};
	tGameover.setOrigin(tGameover.getLocalBounds().width/2.f, tGameover.getLocalBounds().height/2.f);
	tGameover.setPosition(videoMode.width/2.f, videoMode.height/2.f - 128);

	// Texto Final Score
	tFinalScore = sf::Text{"Score: ", font, 32};
	tFinalScore.setOrigin(tFinalScore.getLocalBounds().width/2.f, tFinalScore.getLocalBounds().height/2.f);
	tFinalScore.setPosition(videoMode.width/2.f - 40, videoMode.height/2.f);	

	// Texto Pause
	tPause = sf::Text{"PAUSADO", font, 64};
	tPause.setOrigin(tPause.getLocalBounds().width + 10, tPause.getLocalBounds().height + 10);
	tPause.setPosition(videoMode.width - 20, videoMode.height - 20);	

	// Texto Instrução
	tInstrucao = sf::Text{"Aperte Enter para iniciar", font, 64};
	tInstrucao.setOrigin(tInstrucao.getLocalBounds().width/2, tInstrucao.getLocalBounds().height/2);
	tInstrucao.setPosition(videoMode.width/2.f, videoMode.height/2.f);	

	// Texto Extra (Menu Inicial)
	tExtra = sf::Text{L"2021 - Criado por Bruno L., Daniel K., Jo\u00e3o D.", font, 16};
	tExtra.setOrigin(tExtra.getLocalBounds().width/2, tExtra.getLocalBounds().height/2);
	tExtra.setPosition(videoMode.width/2.f, videoMode.height - 20);

	// Texto Instrução GameOver
	tInstrucaoGO = sf::Text{"Aperte Enter para reiniciar", font, 32};
	tInstrucaoGO.setOrigin(tInstrucaoGO.getLocalBounds().width/2, tInstrucaoGO.getLocalBounds().height/2);
	tInstrucaoGO.setPosition(videoMode.width/2.f, videoMode.height - tInstrucaoGO.getLocalBounds().height - 10);	

}

//InitializeWindow(): Inicializa a janela com as especificações necessárias
void Game::initializeWindow(){
	videoMode.height = HEIGHT;
	videoMode.width = WIDTH;
	window = new sf::RenderWindow(videoMode, "Me-OW!", sf::Style::Titlebar | sf::Style::Close);

	//Carrega e seta a imagem do jogo
	sf::Image icon;
	if(!icon.loadFromFile("resources/icon2.png")){ //Imagem quadrada 128x128
		std::cout<<"Falha na leitura do ícone" << std::endl;
	}
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

/*
* *initializeObjects(): Inicializa a fila de objetos a serem gerados e a lista de objetos spawnados
*/
void Game::initializeObjects(float dt){

	int numObjs = log(level) * 6 + 3; //incrementa o numero de objetos por fase com base no level da fase
	if (numObjs > 1000) numObjs = 1000;

	std::srand(time(0));  //inicializando seed aleatoria

	generateQueue(numObjs, dt); //definir regra de geração pra queue (etapa de fase)
}
/*
* initializePlayer(): Inicializa a posição do player
*/
void Game::initializePlayer(){

	player.setPosition(videoMode.width/2, videoMode.height/2);
}

/*
* generateQueue(int size): Gera a fila de objetos de acordo com um parâmetro decidido no inicio de cada fase
*/
void Game::generateQueue(int size, float dt){
	int key = level >= 5 ? std::rand() % 2 + 1 : 1; //chave que decide o tipo de fase
	player.playNextLevel(); //som de quando passa de fase

	for (int i = 0; i < size; i++){
		objects.newObject(level, window->getSize().x, window->getSize().y, dt, 
								player.getSpriteSize().height, player.getSpriteSize().width, key);
	}
}

//pollEvents(): Verifica eventos (Teclado, Janela aberta)
void Game::pollEvents(float dt){
	//Event polling
	while (window->pollEvent(ev)){
		if (ev.type == sf::Event::Closed) //Fecha a janela do jogo ao clicar no "X" da janela
			window->close();

		if (ev.type == sf::Event::KeyPressed){
			//movimento do player
			if (state == 2) {

				if (ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::W) {
					player.rotateDirection('u', dt);
				}
				else if (ev.key.code == sf::Keyboard::Right || ev.key.code == sf::Keyboard::D) {
					player.rotateDirection('r', dt);
				}
				else if (ev.key.code == sf::Keyboard::Down || ev.key.code == sf::Keyboard::S) {
					player.rotateDirection('d', dt);
				}
				else if (ev.key.code == sf::Keyboard::Left || ev.key.code == sf::Keyboard::A) {
					player.rotateDirection('l', dt);
				}
			}

			//start game
			if (ev.key.code == sf::Keyboard::Enter && (state == 0 || state == 3)) {
				start = !start;
			}

			//pause and unpause
			if (ev.key.code == sf::Keyboard::Escape && (state == 2 || state == 4)) {
				pause = !pause;
			}
		}

	}
}
/*
* setSpawnTimer(): setta o timer de spawn do objeto com base no level
*/

sf::Time Game::setSpawnTimer() {
	if (level == 1) 
		return sf::seconds(1.5f);
	else if(level > 1 && level <=5){
		return sf::seconds(1.f);
	}
	else if (level > 5 && level <= 15) {
		return sf::seconds(0.6f);
	}
	else if (level > 15 && level % 5 == 0) {
		return sf::seconds(0.35f);
	}
	else if (level > 15 && level % 5 != 0) {
		return sf::seconds(0.5f);
	}
}

// updateObjects(): Atualiza as informações dos objetos
void Game::updateObjects(float dt) {
	sf::Time delay = setSpawnTimer(); //delay entre spawns de objetos

	increaseTimer(dt, &spawnTimer);

	if (objects.isEmpty() == false) {

		if (inGame == true) checkerTimer = (LastObjTimer - spawnTimer) + delay; // tempo minimo entre um objeto e o outro

		if (spawnTimer.asSeconds() >= delay.asSeconds()) {
			sf::Time test = objects.getFirst().getHitTime();
			if (test.asSeconds() > checkerTimer.asSeconds()) {

				LastObjTimer = objects.getFirst().getHitTime(); //tempo ate colisao do ultimo objeto spawnado

				spawnObject();

				spawnTimer = sf::seconds(0.f); //restarta timer de spawn de objetos
			}

		}
	}

	if(inGame == true){
		//std::cout << "Num elem na lista: " << spawnedObjects.getNroElementos() << std::endl;

		if (spawnedObjects.getNroElementos() != 0) { //se tiver elementos na lista de spawn, os movimenta
			for (int i = 0; i < spawnedObjects.getNroElementos(); i++) {
					spawnedObjects.getObjects()->moveObject(dt);             /**Marcação para uns testes futuros ai**/
			}
		}
		else if (objects.isEmpty() == true) { //se nao, passou de fase
			pass = true;
		}
	}
	
}

/*
* increaseTimer(float dt, sf::Time *timer): Atualiza o timer desejado
*/
void Game::increaseTimer(float dt, sf::Time *timer) {
	sf::Time increase = sf::seconds(1.f);

	*timer += increase * dt; 
}

/*
* testCollision(): Testa colisões entre obstáculos e o jogador
*/
void Game::testCollisions(){

	Object* testObject;
	for (int i = 0; i < spawnedObjects.getNroElementos(); i++){

		testObject = spawnedObjects.getObjects();

		if(player.collidePlayer(testObject->getBody())){ // Colisão com player
			player.playHurt();
			spawnedObjects.removeObject();
		} 
		else if(player.collideShields(testObject->getBody())){ // Colisão com escudos
			player.playHitShield();
			spawnedObjects.removeObject();
			score += 100 + (testObject->getSpeed()) / 10;	
		}
	}
}

/*
* spawnObject(): Checa se existem objetos a serem spawnados, e se houver, o coloca na lista de spawn
*/
void Game::spawnObject(){
	Object* object = nullptr;
	if (objects.isEmpty() == false){
		object = objects.removeObject();
		spawnedObjects.newObject(object);
		inGame = true;
	}
}

//renderObjects(): Desenha os inimigos na tela
void Game::renderObjects(){
	for (int i = 0; i < spawnedObjects.getNroElementos(); i++){
		(window)->draw(spawnedObjects.getObjects()->getBody());
	}
	
}

//renderScore(): Desenha Pontuação e Vida
void Game::renderScore(){
	tHP.setString("HP: " + std::to_string(hp));
	tScore.setString("Score: " + std::to_string(score));
	nivel.setString("Level: " + std::to_string(level));
	window->draw(nivel);
	window->draw(tHP);
	window->draw(tScore);
	
}
/*
* renderGameOver(): Desenha os textos da tela de gameover
*/
void Game::renderGameOver(){
	tFinalScore.setString("Score: " + std::to_string(score));
	window->draw(tFinalScore);
	window->draw(tGameover);
	window->draw(tInstrucaoGO);
}
/*
* renderPause(): Desenha os textos da tela de pause
*/
void Game::renderPause(){
	timerPause++;
	if(timerPause > 1500){
		piscaPisca = !piscaPisca;
		timerPause = 0;
	}

	if(piscaPisca){
		window->draw(tPause);
	}
	
}

/*
* renderGameOver(): Desenha os textos da tela Inicial
*/
void Game::renderInicial(){

	timerPause++;
	if(timerPause > 2200){
		piscaPisca = !piscaPisca;
		timerPause = 0;
	}

	if(piscaPisca){
		window->draw(tInstrucao);
	}

	window->draw(tExtra);
}