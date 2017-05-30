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
	moveX = moveY = 0;
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
	moveX = moveY = 0;

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
			moveY += velocidad;
		}
		else if (rect.y > rectPJ.y) //movimiento en el eje y
		{
			y = -velocidad;
			moveY += y;
		}
		else if (rect.y < rectPJ.y)
		{
			y = velocidad;
			moveY += y;
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
			moveX += x;
		}
		else if (rect.x > rectPJ.x) //movimiento en el eje x
		{
			x = -velocidad;
			moveX += x;
		}
		else if (rect.x < rectPJ.x)
		{
			x = velocidad;
			moveX += x;
		}


		if (chocando)
			ejeY = true;
	}
	mover(moveX, moveY);
}

void Enemigo::perseguir(){
	cout << "ataco";

	moveX = moveY = 0;

	if (rect.y > rectPJ.y) //movimiento en el eje y
		moveY -= velocidad;
	else if (rect.y < rectPJ.y)
		moveY += velocidad;

	if (rect.x > rectPJ.x) //movimiento en el eje x
		moveX -= velocidad;
	else if (rect.x < rectPJ.x)
		moveX += velocidad;

	mover(moveX, moveY);
}

void Enemigo::mover(int x, int y)
{
	rect.x += x;
	rect.y += y;
}
void Enemigo::pegar(float daño){

	if (pMundo->checkCollision(rectPJ, rect))
	{
		pMundo->getPersonaje()->restaVida(daño);
	}
}

Enemigo::~Enemigo()
{
}




