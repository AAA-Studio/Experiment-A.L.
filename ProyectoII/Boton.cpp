#include "Boton.h"
#include <iostream>
Boton::Boton(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto, CallBack_t * cb) : Entidad(pJ, x, y, textura, efecto, ONull)
{
	rect.h = 100;
	rect.w = 400;
	cboton = cb;
}


Boton::~Boton()
{
}

void Boton::onInput(){
	
	int posMouseX, posMouseY;
	pJuego->getMousePos(posMouseX, posMouseY);

	//Comprobamos si la pos del ratón coincide con la pos de la textura del globo
	if (dentro(posMouseX, posMouseY)){
		cboton(pJuego);
	}
}

bool Boton::dentro(int x, int y)const
{
	return (x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + rect.h));
}

