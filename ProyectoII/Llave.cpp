#include "Llave.h"


Llave::Llave(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto) : Entidad(pJ, x, y, textura, efecto)
{
	visible = true;
}

void Llave::coger(){
	if (visible)
		visible = false;
}

void Llave::soltar(double x, double y){
	if (!visible){
		rect.x = x;
		rect.y = y;
		visible = true;
	}
}
Llave::~Llave()
{
}
