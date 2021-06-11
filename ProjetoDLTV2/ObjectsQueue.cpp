#include "ObjectsQueue.h"


//**Construtores e Destrutores**
ObjectsQueue::ObjectsQueue(int Tamanho)
{
	this->Tamanho = Tamanho;
	InitializeQueue();
}

ObjectsQueue::~ObjectsQueue()
{
}

//InitializeQueue(): Inicializa os atributos da Fila de objetos

void ObjectsQueue::InitializeQueue()
{
	this->Primeiro = nullptr;
	this->Ultimo = nullptr;
	this->NroElementos = 0;
}

void ObjectsQueue::newObject()
{
	Nodeptr Aux; //ponteiro auxiliar

	Aux = new Node;

	Aux->info.InitializeObject();

	//Caso 1: Caso a fila esteja vazia
	if (this->Tamanho == 0)
	{
		this->Primeiro = Aux;
		this->Ultimo = Aux;

		Aux->Dir = Aux; 
		Aux->Esq = Aux;

		this->Tamanho++;
	}

	//Caso 2: Caso a fila tenha apenas um elemento
	else if (this->Tamanho == 1)
	{
		this->Ultimo = Aux;
		(this->Primeiro)->Dir = Aux;
		(this->Primeiro)->Esq = Aux;

		Aux->Dir = this->Primeiro;
		Aux->Esq = this->Primeiro;
	}

	//Caso 3: Caso tenha mais de um elemento

	else if (this->Tamanho > 1)
	{
		(this->Ultimo)->Dir = Aux;
		Aux->Esq = this->Ultimo;

		(this->Primeiro)->Esq = Aux;
		Aux->Dir = this->Primeiro;

		this->Ultimo = Aux;
	}

