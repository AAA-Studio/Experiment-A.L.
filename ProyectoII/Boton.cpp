#include "Boton.h"
#include <iostream>
Boton::Boton(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto, CallBack_t * cb) : Entidad(pJ, x, y, textura, efecto)
{
	cboton = cb;
}


Boton::~Boton()
{
}

void Boton::onInput(){
	
	std::cout << "jugar";
	int posMouseX, posMouseY;
	pJuego->getMousePos(posMouseX, posMouseY);

	//Comprobamos si la pos del ratón coincide con la pos de la textura del globo
	if (dentro(posMouseX, posMouseY)){
		cboton(pJuego);
	}
}

bool Boton::dentro(int x, int y)const
{
	
	return (x >= posX && x <= (posX + ancho) && y >= posY && y <= (posY + alto));
}

