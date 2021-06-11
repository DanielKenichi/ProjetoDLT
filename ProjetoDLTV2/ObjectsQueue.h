#ifndef OBJECTSQUEUE_H
#define OBJECTSQUEUE_H

/*
* Fila de objetos atirados na dire��o do jogador
*/

//**bibliotecas e includes**
#include "Object.h"



//**structs**
struct Node
{
    Object info;
    struct Node* Dir;
    struct Node* Esq;

};

typedef struct Node* Nodeptr;

//**Classe FilaObjetos**
class ObjectsQueue {

public:
    //**Construtor e destrutor**
    ObjectsQueue(int Tamanho);
    ~ObjectsQueue();

    //**m�todos get ** 
    int getTamanho();


    //**M�todos primitivos**
     void InitializeQueue();
     void newObject();



private:
    //**Atributos da Pilha**
    int Tamanho;

    Nodeptr Primeiro;
    Nodeptr Ultimo;

    int NroElementos;


};

#endif //OBJECTSQUEUE_H

