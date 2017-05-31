#include "BossFinal.h"
#include "Personaje.h"

BossFinal::BossFinal(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto) 
: Enemigo(pM, x, y, w, h, textura, efecto)
{
	vida = 10;
	velocidad = 1;
	timeR = 500;
	passedTime = 0;
	comportamiento = EPersigue;
	estoyCerca = false;
	dist = rect;
	rangoDist = 10;
	embistiendo;
}
BossFinal::~BossFinal(){}


void BossFinal::update()
{
	rectPJ = pMundo->getPersonaje()->getRect(); //rect del personaje

	switch (comportamiento)
	{
	case ERecarga:
		passedTime++;
		recargando();
		break;
	case EPersigue:
		perseguir();
		break;
	case EEmbiste:
		passedTime++;
		cout << "tengo que embestir";
		embestir();
		break;
	case EDispara1:
		break;
	default:
		break;
	}
}

void BossFinal::recargando(){
	if (passedTime >= timeR)
	{
		comportamiento = EPersigue;
		passedTime = 0;
	}
}

void BossFinal::perseguir(){

	moveX = moveY = 0;
	dist = rect;

	if (rect.y > rectPJ.y) //movimiento en el eje y
	{
		moveY -= velocidad;
	}
	else if (rect.y < rectPJ.y)
	{
		moveY += velocidad;
		
	}
	if (rect.x > rectPJ.x) //movimiento en el eje x
		moveX -= velocidad;
	else if (rect.x < rectPJ.x)
		moveX += velocidad;

	dist.x += rangoDist * moveX;
	dist.y += rangoDist * moveY;

	if (!pMundo->checkCollision(dist, rectPJ))
		mover(moveX, moveY);
	else
	{
		comportamiento = EEmbiste;
		xPJ = rectPJ.x;
		yPJ = rectPJ.y;
		embistiendo = true;
	}
}

void BossFinal::embestir(){
	

}

