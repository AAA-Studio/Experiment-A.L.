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

	rect = { x, y, 59, 75 };
	rectAn = { 0, 0, 59, 75 };	//medidas del rect de la animacion
	retardo = 0;
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

	moveX = moveY = 0;

	if (rect.y > rectPJ.y) //movimiento en el eje y
	{
		moveY -= velocidad;
	}
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

	if (moveX == 0 && moveY > 0)
	{
		animacion(abajo);
	}
	else if (moveX == 0 && moveY < 0)
	{
		animacion(arriba);
	}
	else if (moveX > 0 && moveY == 0){
		animacion(derecha);
	}
	else if (moveX < 0 && moveY == 0){
		animacion(izquierda);
	}
	else if (moveX < 0 && moveY < 0){
		animacion(izquierda);
	}
	else if (moveX > 0 && moveY < 0){
		animacion(derecha);
	}
	else if (moveX < 0 && moveY > 0){
		animacion(izquierda);
	}
	else if (moveX > 0 && moveY > 0){
		animacion(derecha);
	}
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

//El rect de animación va recorriendo la Y del spritesheet
void Enemigo::animacion(animar currentFrame){
	retardo++;
	if (retardo == 7){
		switch (currentFrame){
		case Enemigo::derecha:
			rectAn.y = enemigoDcha;
			retardo = 0;
			break;
		case Enemigo::izquierda:
			rectAn.y = enemigoIzq;
			retardo = 0;
			break;
		case Enemigo::arriba:
			rectAn.y = enemigoArr;
			retardo = 0;
			break;
		case Enemigo::abajo:
			rectAn.y = 0;
			retardo = 0;
			break;
		default:
			break;
		}
		frames();

	}

}

//El rect de animación va recorriendo la X del spritesheet
void Enemigo::frames(){
	if (rectAn.x >= limiteX){
		rectAn.x = 0;
	}
	else{
		rectAn.x += sumaAnimX;
	}
}

//Dibujado con la textura de la animación
void Enemigo::draw(int x, int y)const
{
	//Tiene animación, sobrescribe la herencia
	pJuego->getResources()->getTextura(textura)->draw(pJuego->getRender(), rect, x, y, &rectAn);//Dibujamos la textura

}
