#include "Boton.h"

Boton::Boton(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto, CallBack_t * cb) : Entidad(pJ, x, y, textura, efecto)
{
	cboton = cb;
	rect = { posX, posY, ancho, alto };
}


Boton::~Boton()
{
}

bool Boton::onClick(){
	if (Entidad::onClick()){
		cboton(pJuego);
		return true;
	}
	return false;
}

