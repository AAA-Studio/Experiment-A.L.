#include "Enemigo2.h"
#include "Personaje.h"
using namespace std;

Enemigo2::Enemigo2(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto, char dir, int max) : Enemigo(pM, x, y, w, h, textura, efecto)
{

	vida = 3;
	maxX = maxY = max;
	this->x = x;
	this->y = y;
	direccion = true;
	pasivo = true;
	volviendo = false;
	eje = dir;
	velocidad = 1;
}

void Enemigo2::update(){

	rectPJ = pMundo->getPersonaje()->getRect(); //rect del personaje
	checkPersonaje(); //comprobacion de la posicion del personaje
	posXAnt = rect.x;
	posYAnt = rect.y;

	if (volviendo && !pasivo)
	{
		volver();
	}
	else if (pasivo)
		patrulla();
	else
		ataque();
}

void  Enemigo2::patrulla(){
	moveX = moveY = 0;
	if (eje == 'x'){
		if (direccion) //camina hacia la derecha
		{
			moveX += velocidad;
			if (rect.x >= x + maxX)
				direccion = false;
		}
		else //camina hacia la izquierda
		{
			moveX -= velocidad;
			if (rect.x <= x)
				direccion = true;
		}
	}
	else if (eje == 'y')
	{
		if (direccion) //camina hacia la derecha
		{
			moveY += velocidad;
			if (rect.y >= y + maxY)
				direccion = false;
		}
		else //camina hacia la izquierda
		{
			moveY -= velocidad;
			if (rect.y <= y)
				direccion = true;
		}
	}

	mover(moveX, moveY);

}

void Enemigo2::ataque(){
	if (!chocando)
		perseguir();
	else
		rodear();
	pegar(0.005);
}


void Enemigo2::volver(){
	moveX = moveY = 0;

	if (rect.y > y) //movimiento en el eje y
		moveY -= velocidad;
	else if (rect.y < y)
		moveY += velocidad;

	if (rect.x > x) //movimiento en el eje x
		moveX -= velocidad;
	else if (rect.x < x)
		moveX += velocidad;

	if (rect.y == y && rect.x == x) //posicion original
	{

		pasivo = true;
		volviendo = false;
	}

	mover(moveX, moveY);

	
}

void Enemigo2::checkPersonaje(){

	//si el jugador está dentro de un radio de 100 el enemigo le detecta
	if (rectPJ.x <= rect.x + 100 && rectPJ.x >= rect.x - 100 && rectPJ.y <= rect.y + 100 && rectPJ.y >= rect.y - 100)
	{
		pasivo = false;
		volviendo = false;
	}
	else
	{
		volviendo = true;
	}
}
Enemigo2::~Enemigo2()
{
}
