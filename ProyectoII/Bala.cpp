#include "Bala.h"
#include <iostream>
#include "Mundo.h"
#include "Personaje.h"


Bala::Bala(MundoVirtual * pM, int x, int y, Texturas_t textura, Efectos_t efecto, int ang, ListaBalas_t tBala) : Entidad(pM->getPJ(), x, y, textura, efecto, ONull)
{
	incrX = incrY = 0;
	velocidad = 1;
	angulo = ang;
	setAngulo();
	time = SDL_GetTicks();
	tipoBala = tBala;
	pMundo = pM;
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
		list<EntidadJuego*> listaBalas = pMundo->getListaBalas(tipoBala);
		list<EntidadJuego*>::iterator it = listaBalas.begin();
		while (!listaBalas.empty() && it != listaBalas.end() && (*it) != this)
		{
			it++;
		}
		pMundo->destruyeBala(listaBalas, it);
	}

}
