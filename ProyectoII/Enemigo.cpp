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
	if (ejeY)
	{
		if (rect.y == rectPJ.y)
		{
			atascadoY = true;
		}

		if (atascadoY)
		{
			cout << "here";
			cout << velocidad;
			rect.y += velocidad;
		}
		else if (rect.y > rectPJ.y) //movimiento en el eje y
		{
			y = -velocidad;
			rect.y += y;
		}
		else if (rect.y < rectPJ.y)
		{
			y = velocidad;
			rect.y += y;
		}


		/*if (chocando)
		{
			ejeY = false;
			//cout << "no puedo seguir por este camino ";
		}*/
	}
	else if (ejeX)
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
			x = -velocidad;
			rect.x += x;
		}
		else if (rect.x < rectPJ.x)
		{
			x = velocidad;
			rect.x += x;
		}


		if (chocando)
			ejeY = true;
	}
	
}

void Enemigo::perseguir(){


	if (rect.y > rectPJ.y) //movimiento en el eje y
		rect.y -= velocidad;
	else if (rect.y < rectPJ.y)
		rect.y += velocidad;

	if (rect.x > rectPJ.x) //movimiento en el eje x
		rect.x -= velocidad;
	else if (rect.x < rectPJ.x)
		rect.x += velocidad;
}

Enemigo::~Enemigo()
{
}




