#include "Enemigo.h"
#include "Bala.h"


Enemigo::Enemigo(MundoVirtual*pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto) : Entidad(pM->getPJ(), x, y, w, h, textura, efecto, ONull)
{
	vida = 3;
	angulo = 180;
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
		pMundo->insertaBala(LBalasEnemigos, new Bala(pMundo, rect.x, rect.y, rect.w, rect.h, JuegoSDL::TFuego, JuegoSDL::ENull, 177, LBalasEnemigos));

		ultimaBala = SDL_GetTicks();
	}
}



