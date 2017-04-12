#include "Tecla.h"


Tecla::Tecla(Juego* pJ, int x, int y, Texturas_t textura, Efectos_t efecto, CallBack_t * cb, int numero) : Entidad(pJ, x, y, textura, efecto, ONull)

{
	cboton = cb;
	this->numero = numero;
	
}

void Tecla::onInput(){

	int posMouseX, posMouseY;
	pJuego->getMousePos(posMouseX, posMouseY);

	//Comprobamos si la pos del ratón coincide con la pos de la textura del globo
	if (dentro(posMouseX, posMouseY)){
		cboton(numero);
	}
}


Tecla::~Tecla()
{
}
