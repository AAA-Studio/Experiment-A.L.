#include "Enemigo5.h"
#include "Personaje.h"
#include "Bala.h"
#include <time.h>

Enemigo5::Enemigo5(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto)
	: Enemigo(pM, x, y, w, h, textura, efecto)
{

	vida = 5;
	velocidad = 2;
}


Enemigo5::~Enemigo5()
{
}

void Enemigo5::update() {

	rectPJ = pMundo->getPersonaje()->getRect();
	srand(time(NULL));
	int aleatorio = (rand() % 50);
	
	if (aleatorio > 42) { // Se mueve a la posicion anterior del jugador
		movimiento();
	}

	else {
		disparar();
	}

	destino.first = rectPJ.x;
	destino.second = rectPJ.y;
}

void Enemigo5::movimiento() {

	if (rect.y > destino.second) { //movimiento en el eje y
		
		rect.y -= velocidad;
	}
	else if (rect.y < destino.second) {
		
		rect.y += velocidad;
	}

	if (rect.x > destino.first) { //movimiento en el eje x
		
		rect.x -= velocidad;
	}
	else if (rect.x < destino.first) {
		
		rect.x += velocidad;
	}

}

void Enemigo5::disparar() {
	if (SDL_GetTicks() - ultimaBala >= tiempoBala)
	{
		SDL_Rect rectPj = pMundo->getPersonaje()->getRect();
		SDL_Rect rectDisparo = { rect.x + rect.w / 2, rect.y + rect.h / 2, rect.w, rect.h };

		//Hallamos el angulo entre el personaje y el enemigo
		if ((rectPj.x - rect.x) != 0)
			angulo = atan2((float)(rectDisparo.y - (rectPj.y + rectPj.h)), -(float)(rectDisparo.x - (rectPj.x + rectPj.w / 2))) * 180 / 3.14;

		//Instanciamos la bala
		pMundo->insertaBala(LBalasEnemigos, new Bala(pMundo, rectDisparo.x, rectDisparo.y, rect.w / 5, rect.h / 5,
			JuegoSDL::TFuego, JuegoSDL::ENull, angulo, LBalasEnemigos));

		ultimaBala = SDL_GetTicks();
	}
}
