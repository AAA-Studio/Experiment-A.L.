#include "BossFinal.h"
#include "Personaje.h"
#include "Bala.h"

BossFinal::BossFinal(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto)
: Enemigo(pM, x, y, w, h, textura, efecto)
{
	vida = 10;
	velocidad = 1;
	timeR = 50;
	timeE = 2;
	timeA = 60;
	timeC = 20;
	passedTime = 0;
	comportamiento = EPersigue;
	estoyCerca = false;
	dist = rect;
	rangoDist = 40;
	embistiendo = false;
	llegado = false;
	angulo = 0;

	rect = { x, y, 85, 76 };
	rectAn = { 0, 0, 85, 76 };	//medidas del rect de la animacion

	enemigoDcha = 193;
	enemigoArr = 288;
	enemigoIzq = 98;
	sumaAnimX = 105;
	limiteX = 183;
}

BossFinal::~BossFinal(){}


void BossFinal::update()
{

	rectPJ = pMundo->getPersonaje()->getRect(); //rect del personaje
	posXAnt = rect.x;
	posYAnt = rect.y;
	pegar(0.008);
	passedTime++;

	switch (comportamiento)
	{
	case ERecarga:
		recargando();
		break;
	case EPersigue:
		perseguir();
		break;
	case EEmbiste:
		embestir();
		break;
	default:
		break;
	}
}

void BossFinal::recargando(){
	if (!embistiendo)
	{
		if (passedTime >= timeR)
		{
			passedTime = 0;
			comportamiento = EPersigue;
		}
	}
	else
	{
		if (passedTime >= timeE)
		{
			passedTime = 0;
			velocidad = 5;
			yPJ = rectPJ.y;
			xPJ = rectPJ.x;
			comportamiento = EEmbiste;
		}
	}
}

void BossFinal::perseguir(){

	if (passedTime >= timeA)
	{
		passedTime = 0;
		embistiendo = true;
		comportamiento = ERecarga;
	}
	else
	{
		if (rand() % 100 <= 25)
			disparo();
		if (!chocando)
			Enemigo::perseguir();
		else
			rodear();
	}


}

void BossFinal::embestir(){
	if (embistiendo)
	{
		if (passedTime < timeC)
		{
			//cout << "persigo";
			cargarContraPJ(); //le persigo de forma que cargo contra el 
		}
		else
		{
			passedTime = 0;
			embistiendo = false;
		}
	}
	else
	{
		velocidad = 1; //si he llegado a la posicion, cambio la velocidad y dejo de embestir
		comportamiento = ERecarga; //cuando acabo de embestir me paro y recargo
	}
}

void BossFinal::cargarContraPJ(){

	moveX = moveY = 0;

	if (rect.y > yPJ) //movimiento en el eje y
	{
		moveY -= velocidad;
	}
	else if (rect.y < yPJ)
		moveY += velocidad;

	if (rect.x > xPJ) //movimiento en el eje x
		moveX -= velocidad;
	else if (rect.x < xPJ)
		moveX += velocidad;

	mover(moveX, moveY);
}

void BossFinal::disparo(){
	if (SDL_GetTicks() - ultimaBala >= tiempoBala)
	{
		SDL_Rect rectPj = pMundo->getPersonaje()->getRect();
		SDL_Rect rectDisparo = { rect.x + rect.w / 2, rect.y + rect.h / 2, rect.w, rect.h };

		//Hallamos el angulo entre el personaje y el enemigo
		if ((rectPj.x - rect.x) != 0)
			angulo = atan2((float)(rectDisparo.y - (rectPj.y + rectPj.h)), -(float)(rectDisparo.x - (rectPj.x + rectPj.w / 2))) * 180 / 3.14;

		//Instanciamos la bala
		pMundo->insertaBala(LBalasEnemigos, new Bala(pMundo, rectDisparo.x, rectDisparo.y, rect.w / 5, rect.h / 5, JuegoSDL::TFuego, JuegoSDL::ENull, angulo, LBalasEnemigos));

		ultimaBala = SDL_GetTicks();
	}
}