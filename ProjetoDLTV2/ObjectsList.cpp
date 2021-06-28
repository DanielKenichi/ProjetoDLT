#include "ObjectsList.h"

/*Construtor e Destrutor*/
ObjectsList::ObjectsList(){
	initializeList();
}

ObjectsList::~ObjectsList(){
	std::cout << "Lista destruida" << std::endl;
}
/**setters**/
void ObjectsList::setAtt(){
	att = PL;
}

/**getters**/
int ObjectsList::getNroElementos(){
	return NroElementos;
}

/*
* getObjects(): 
*/
Object* ObjectsList::getObjects() {
	LNodeptr Aux;
	Aux = att; //Identifica o objeto a ser atualizado em um loop

	if (PL == NULL){
		std::cout << "Acabou a os objetos da lista" << std::endl;
		return NULL;
	}
	else{	
		att = (att)->Next;
		return &(Aux->Next)->info;
	}	
}

/*
* initializeList(): Inicializa a lista de objetos, indicando quais objetos estão spawnados
*/
void ObjectsList::initializeList(){
	PL = nullptr;
	UL = nullptr;
	att = nullptr;
	NroElementos = 0;
}
/*
* newObject(): Insere um novo objeto na lista para ser spawnado
*/

void ObjectsList::newObject(Object *obj){
	
	LNodeptr Aux;

	Aux = new LNode;

	Aux->info = *obj;

	//Caso 1: Caso a lista esteja vazia
	if (NroElementos == 0){
		att = Aux;
		PL = Aux;
		UL = Aux;

		Aux->Next = Aux;

		NroElementos++;
	}

	//Caso 2: Caso a lista tenha apenas um elemento
	else if (NroElementos == 1){
		UL = Aux;
		PL->Next = Aux;

		Aux->Next = PL;
		att = UL;

		NroElementos++;
	}

	//Caso 3: Caso tenha mais de um elemento

	else if (NroElementos > 1){
		UL->Next = Aux;
		UL = Aux;

		Aux->Next = PL;

		att = UL;

		NroElementos++;
	}

}

void ObjectsList::removeObject(){
	//caso 0: lista vazia
	if (NroElementos == 0){
		std::cout << "Não há objetos a serem removidos" << std::endl;
	}

	//caso 1: a lista tem apenas um elemento
	else if (NroElementos == 1){
		PL->Next = nullptr;

		delete PL;

		PL = nullptr;
		UL = nullptr;
		att = nullptr;

		NroElementos--;
	}

	//caso 2: a lista tem mais de um elemento...
	else if (NroElementos > 1){
		LNodeptr anterior = PL;

		//caso 2.1 ...e o elemento a ser removido esteja no começo da lista
		if (att == PL){
			PL = PL->Next;
			UL->Next = PL;
			att->Next = nullptr;

			delete att;

			att = PL;
			NroElementos--;
		}

		else if (att == UL) {
			while (anterior->Next != att){
				anterior = anterior->Next;
			}

			anterior->Next = att->Next;

			att->Next = nullptr;
			delete att;

			att = anterior->Next;
			UL = anterior;
			NroElementos--;
		}

		//caso 2.2 ... e o elemento a ser removido esteja no meio da lista
		else{
			while (anterior->Next != att){
				anterior = anterior->Next;
			}
			anterior->Next = att->Next;

			att->Next = nullptr;
			delete att;

			att = anterior->Next;
			NroElementos--;
		}

	}

}


