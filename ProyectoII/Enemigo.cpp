#include "Enemigo.h"
#include "Bala.h"
#include <iostream>
#include "Personaje.h"

Enemigo::Enemigo(MundoVirtual*pM, int x, int y, int w, int h,int vida, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto) : Entidad(pM->getPJ(), x, y, w, h, textura, efecto, ONull)
{
	this->vida = vida;
	angulo = 0;
	pMundo = pM;
	primerTiro = 0;
}


Enemigo::~Enemigo()
{
}

void Enemigo::update(){
	disparo();
	primerTiro++;
}

void Enemigo::disparo(){
	if (SDL_GetTicks() - ultimaBala >= tiempoBala && primerTiro > 50)
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



