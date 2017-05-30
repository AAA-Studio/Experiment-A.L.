#include "Enemigo1.h"
#include "Bala.h"
#include <iostream>
#include "Personaje.h"

Enemigo1::Enemigo1(MundoVirtual*pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto) : Enemigo(pM, x, y, w, h, textura, efecto)
{
	vida = 3;
	angulo = 0;
	pMundo = pM;
}


Enemigo1::~Enemigo1()
{
}

void Enemigo1::update(){
	disparo();
}

void Enemigo1::disparo(){
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



