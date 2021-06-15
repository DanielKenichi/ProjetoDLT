#ifndef OBJECTSLIST_H
#define OBJECTSLIST_H

/*
* Fila de objetos atirados na direção do jogador
*/

//**bibliotecas e includes**
#include "Object.h"



//**structs**
 
struct LNode
{
    Object info;
    struct LNode* Next;
};

typedef struct LNode* LNodeptr;

//**Classe ListaObjetos**
class ObjectsList {

public:
    //**Construtor e destrutor**
    ObjectsList();
    ~ObjectsList();

    //**setters**
    void setAtt();

    //**getters** 
    int getNroElementos();
    Object* getObjects();
    //**Métodos primitivos**
    void initializeList();
    void newObject(Object* obj);
    void removeObject();



private:
    //**Atributos da Lista**
    LNodeptr PL; 
    LNodeptr UL;

    LNodeptr att;

    int NroElementos;


};

#endif //OBJECTSLIST_H

