#include "Bala.h"
#include <iostream>


Bala::Bala(MundoVirtual * pM, int x, int y, int ancho, int alto, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto, float ang, ListaBalas_t tBala) 
	: Entidad(pM->getPJ(), x, y, ancho, alto, textura, efecto, ONull)
	, pMundo(pM), angulo(ang), tipoBala(tBala)
{
	incrX = incrY = 0;
	velocidad = 10;
	setAngulo();
	time = SDL_GetTicks();
}

Bala::~Bala(){}

//Dependiendo del ángulo recibido, establece el incremento en x e y
void Bala::setAngulo(){
	angulo = (angulo * 2 * 3.14) / 360;
	incrX = cos(angulo);
	incrY = -sin(angulo);
}



void Bala::update(){
	rect = { rect.x + incrX * velocidad, rect.y + incrY * velocidad, rect.w, rect.h };
}
