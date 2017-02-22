#include "Objetos.h"


Objetos::Objetos(int px, int py, Texturas_t text)
{
	rectObjeto.x = px;
	rectObjeto.y = py;
	textura = text;
}

//dibuja el objeto si es visible y sino no
void Objetos::dibujar(){
	//if (visible)
}

//en el caso de que se coja un objeto se vuelve invisble y se a�ade a la mochila
void Objetos::coger(){
	if (visible && colision){//se puede coger si se colisiona con el objeto y se puede ver
		visible = false; //si se coge no destruimos el objeto, es invisible y est� en la mochila
		//llamada a metodo de almacenamiento en mochila para a�adir el objeto
	}
}

//si el jugador suelta un objeto desde la mochila llama a este m�todo para que sea visible y 
//se asignan sus nueva posicion x e y
void Objetos::soltar(){
	//destruir
}

Objetos::~Objetos()
{
}
