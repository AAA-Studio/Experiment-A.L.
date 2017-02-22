#include "Objetos.h"


Objetos::Objetos(int px, int py) 
{
	x = px;
	y = py;
}

//dibuja el objeto si es visible y sino no
void Objetos::dibujar(){
	//if (visible)
}

//en el caso de que se coja un objeto se vuelve invisble y se añade a la mochila
void Objetos::coger(){
	if (visible && colision){//se puede coger si se colisiona con el objeto y se puede ver
		visible = false; //si se coge no destruimos el objeto, es invisible y está en la mochila
		//llamada a metodo de almacenamiento en mochila para añadir el objeto
	}
}

//si el jugador suelta un objeto desde la mochila llama a este método para que sea visible y 
//se asignan sus nueva posicion x e y
void Objetos::soltar(int px, int py){
	visible = true;
	x = px;
	y = py;
}

Objetos::~Objetos()
{
}
