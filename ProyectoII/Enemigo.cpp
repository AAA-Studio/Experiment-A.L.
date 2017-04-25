#include "Enemigo.h"
#include "Bala.h"


Enemigo::Enemigo(MundoVirtual*pM, int x, int y,int w ,int h, Texturas_t textura, Efectos_t efecto) : Entidad(pM->getPJ(), x, y,w,h, textura, efecto, ONull)
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
		pMundo->insertaBala(LBalasEnemigos, new Bala(pMundo, rect.x, rect.y, TFuego, ENull, 177, LBalasEnemigos, rect.w,rect.h));

		ultimaBala = SDL_GetTicks();
	}
}



