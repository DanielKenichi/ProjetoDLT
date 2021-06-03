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
