#include "ObjectsQueue.h"


//**Construtores e Destrutores**
ObjectsQueue::ObjectsQueue(){
	initializeQueue();
}

ObjectsQueue::~ObjectsQueue(){
	std::cout << "Fila destruida" << std::endl;
}

Object ObjectsQueue::getFirst()
{
	return (this->Primeiro)->info;
}


bool ObjectsQueue::isEmpty()
{
	if (NroElementos == 0){
		return true;
	}

	else{
		return false;
	}
	
}


//InitializeQueue(): Inicializa os atributos da Fila de objetos
void ObjectsQueue::initializeQueue(){
	Primeiro = nullptr;
	Ultimo = nullptr;
	NroElementos = 0;
}

/*
* newObject(): Inicializa e insere um novo objeto na fila de objetos (sem prioridade ainda)
*/

void ObjectsQueue::newObject(int level, int w, int h, float dt, int ph, int pw, int key){
	Nodeptr Aux; 

	Aux = new Node;

	Aux->info.initializeObject(level, h, w, dt, ph, pw, key); 

	//Caso 1: Caso a fila esteja vazia
	if (NroElementos == 0){
		Primeiro = Aux;
		Ultimo = Aux;

		Aux->Next = Aux;

		NroElementos++;
	}

	//Caso 2: Caso a fila tenha apenas um elemento
	else if (NroElementos == 1){
		Ultimo = Aux;
		Primeiro->Next = Aux;

		Aux->Next = Primeiro;
		NroElementos++;
	}

	//Caso 3: Caso tenha mais de um elemento

	else if (NroElementos > 1){
		Ultimo->Next = Aux;
		Ultimo = Aux;

		Aux->Next = Primeiro;

		NroElementos++;
	}
}
/*
* removeObject(): Remove da fila o objeto para ser transferido para a lista de spawnados
*/
Object* ObjectsQueue::removeObject(){
	Nodeptr Aux; 

	Aux = Primeiro;

	//Caso 1: A fila está vazia
	if (NroElementos == 0){
		std::cout << "Falha no spawn do objeto (fila vazia)" << std::endl;
	}

	//Caso 2: A fila tem apenas um elemento
	else if (NroElementos == 1){
		Aux->Next = nullptr;


		Primeiro = nullptr;
		Ultimo = nullptr;

		NroElementos--;

		return &Aux->info;
	}

	//Caso 3: A fila tem mais de um elemento
	else if (NroElementos > 1){
		Primeiro = (Primeiro)->Next;

		Ultimo->Next = Primeiro;

		Aux->Next = nullptr;

		NroElementos--;

		return &Aux->info;
	}
}
