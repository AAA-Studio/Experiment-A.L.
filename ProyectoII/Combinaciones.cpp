#include "Combinaciones.h"
#include "Tecla.h"
using namespace std;

static int numero(int num){ return num; }

Combinaciones::Combinaciones(Juego* juego)
{
	this->juego = juego;
}

void Combinaciones::initObjetos(){
	objetos[0] = new Tecla(juego, 100, 100, TExit, ENull, numero, 0);
}

void Combinaciones::onInput(SDL_Event &e){

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			int i = 0;
			while (i < objetos.size())
			{
				objetos[i]->onInput();
				i++;
			}
		}
	}
}

Combinaciones::~Combinaciones()
{
}
