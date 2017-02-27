#include "Bala.h"
#include <iostream>


Bala::Bala(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto) : Entidad(pJ, x, y, textura, efecto)
{
	incrX = incrY = 0;
	velocidad = 1;
	angulo = 0;
	
}


Bala::~Bala()
{
}

void Bala::setAngulo(int angulo){
	incrX = incrY = 0;
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

void Bala::setPos(int x,int y){
	posX = x;
	posY = y;
	rect = { posX, posY, ancho, alto };

}


void Bala::update(){
	posX += velocidad * incrX;
	posY += velocidad * incrY;
	rect = { posX, posY, ancho, alto };
}
