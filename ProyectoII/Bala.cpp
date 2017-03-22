#include "Bala.h"
#include <iostream>
#include "Mundo.h"
#include "Personaje.h"


Bala::Bala(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto, int ang, PersonajeVirtual* per) : Entidad(pJ, x, y, textura, efecto)
{
	incrX = incrY = 0;
	velocidad = 1;
	angulo = ang;
	setAngulo();
	time = SDL_GetTicks();
	personaje = per;

}


Bala::~Bala()
{
}

//Dependiendo del ángulo recibido, establece el incremento en x e y
void Bala::setAngulo(){
	switch (angulo)
	{
	case 0:
		incrX = 1;
		break;
	case 45:
		incrX = 1;
		incrY = -1;
		break;
	case 90:
		incrY = -1;
		break;
	case 135:
		incrX = -1;
		incrY = -1;
		break;
	case 180:
		incrX = -1;
		break;
	case 225:
		incrX = -1;
		incrY = 1;
		break;
	case 270:
		incrY = 1;
		break;
	case 315:
		incrX = 1;
		incrY = 1;
		break;
	default:
		break;
	}

}



void Bala::update(){

	rect = { rect.x + velocidad * incrX, rect.y +  velocidad * incrY, rect.w, rect.h };
	if (SDL_GetTicks() - time >= duracion)//Se pide la hora y se compara con la última 
	{
		personaje->destruyeBala(this);
	}

}
