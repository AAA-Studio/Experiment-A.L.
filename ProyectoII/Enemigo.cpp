#include "Enemigo.h"
#include "Bala.h"
#include <iostream>
#include "Personaje.h"

Enemigo::Enemigo(MundoVirtual*pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto) : Entidad(pM->getPJ(), x, y, w, h, textura, efecto, ONull)
{
	pMundo = pM;
	this->y = 0;
	this->x = 0;
	posXAnt = x;
	posYAnt = y;
	chocando = false;
	ejeY = true;
	ejeX = true;
	atascadoX = atascadoY = false;
}

void Enemigo::update(){
	rectPJ = pMundo->getPersonaje()->getRect(); //rect del personaje
}

void Enemigo::setPosChocando(int x, int y)
{
	rect.x = x;
	rect.y = y;
}
void Enemigo::rodear()
{
	if (ejeX)
	{
		if (rect.x == rectPJ.x)
			atascadoX = true;

		if (atascadoX)
		{
			cout << "movimiento x ";
			rect.x += x;
		}
		else if (rect.x > rectPJ.x) //movimiento en el eje x
		{
			x = -1;
			rect.x += x;
		}
		else if (rect.x < rectPJ.x)
		{
			x = 1;
			rect.x += 1;
		}


		if (chocando)
			ejeX = false;
	}
	else if (ejeY)
	{
		if (rect.y == rectPJ.y)
		{
			atascadoY = true;
		}

		if (atascadoY)
		{
			rect.y += y;
		}
		else if (rect.y > rectPJ.y) //movimiento en el eje y
		{
			y = -1;
			rect.y += y;
		}
		else if (rect.y < rectPJ.y)
		{
			y = 1;
			rect.y += y;
		}


		if (chocando)
		{
			ejeX = false;
			//cout << "no puedo seguir por este camino ";
		}
	}

	//else
}

void Enemigo::perseguir(){


	if (rect.y > rectPJ.y) //movimiento en el eje y
		rect.y -= 1;
	else if (rect.y < rectPJ.y)
		rect.y += 1;

	if (rect.x > rectPJ.x) //movimiento en el eje x
		rect.x -= 1;
	else if (rect.x < rectPJ.x)
		rect.x += 1;
}

Enemigo::~Enemigo()
{
}




