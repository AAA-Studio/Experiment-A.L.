#include "Bala.h"
#include <iostream>
#include "Mundo.h"
#include "Personaje.h"


Bala::Bala(MundoVirtual * pM, int x, int y, Texturas_t textura, Efectos_t efecto, float ang, ListaBalas_t tBala,int ancho, int alto) : Entidad(pM->getPJ(), x, y, textura, efecto, ONull)
{
	rect.w /= 3;
	rect.h /= 3;

	incrX = incrY = 0;
	velocidad = 1;
	angulo = ang;
	setAngulo(ancho,alto);
	time = SDL_GetTicks();
	tipoBala = tBala;
	pMundo = pM;
}


Bala::~Bala()
{
}

//Dependiendo del ángulo recibido, establece el incremento en x e y
void Bala::setAngulo(int ancho, int alto){

	angulo = (angulo * 2 * 3.14) / 360;
	incrX = cos(angulo);
	incrY = -sin(angulo);


	/*
	switch (angulo)
	{
	case 0:
		incrX = 1;
		rect.x += ancho;
		rect.y += alto / 2 -rect.h / 2;
		break;
	case 45:
		incrX = 1;
		incrY = -1;
		rect.x += ancho;
		rect.y -= rect.h / 2;
		break;
	case 90:
		incrY = -1;
		rect.x += ancho / 2 - rect.w / 2;
		rect.y -= rect.h;

		break;
	case 135:
		incrX = -1;
		incrY = -1;
		rect.x -= rect.w/2;
		rect.y -= rect.h/2;
		break;
	case 180:
		incrX = -1;
		rect.x -= rect.w;
		rect.y += alto / 2 - rect.h / 2;

		break;
	case 225:
		incrX = -1;
		incrY = 1;
		rect.x -= rect.w / 2;
		rect.y += alto;
		break;
	case 270:
		incrY = 1;
		rect.y += alto;
		rect.x += ancho / 2 - rect.w / 2;

		break;
	case 315:
		incrX = 1;
		incrY = 1;
		rect.x += ancho;
		rect.y += alto;
		break;
	default:
		break;
	}
	*/

}



void Bala::update(){

	rect = { rect.x + incrX*10, rect.y +  incrY*10, rect.w, rect.h };
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
