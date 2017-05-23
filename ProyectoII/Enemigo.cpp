#include "Enemigo.h"
#include "Bala.h"
#include <iostream>


Enemigo::Enemigo(MundoVirtual*pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto) : Entidad(pM->getPJ(), x, y, w, h, textura, efecto, ONull)
{
	vida = 3;
	angulo = 0;
	pMundo = pM;
}


Enemigo::~Enemigo()
{
}

void Enemigo::update(){


	disparo();
}

void Enemigo::disparo(){
	if (SDL_GetTicks() - ultimaBala >= tiempoBala)//Se pide la hora y se compara con la última 
	{
		SDL_Rect rectPj = pMundo->getPersonaje()->getRect();
		if ((rectPj.x - rect.x) != 0)
			angulo = 360 * atan2((float)(rectPj.y - rect.y) , (float)(rectPj.x - rect.x)) / (2 * 3.14);
	
		std::cout << angulo << endl;

		pMundo->insertaBala(LBalasEnemigos, new Bala(pMundo, rect.x, rect.y, rect.w, rect.h, JuegoSDL::TFuego, JuegoSDL::ENull, angulo, LBalasEnemigos));

		ultimaBala = SDL_GetTicks();
	}
}



