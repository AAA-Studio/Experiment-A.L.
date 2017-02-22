#include "Pausa.h"
#include "Boton.h"


Pausa::Pausa(Juego * pJ) : Estado(pJ)
{
	objetos.resize(2);
	initObjetos();
}


Pausa::~Pausa()
{
}

void Pausa::initObjetos(){
	objetos[0] = new Boton(pJuego, 270, 150, TMenu, ENull, goMenu);
	objetos[1] = new Boton(pJuego, 270, 250, TPlay, ENull, goPlay);

}

void Pausa::draw()const
{
	//SDL_Rect fondoRect = { 0, 0, pJuego->getAncho(), pJuego->getAlto() };
	//pJuego->getTextura(TFondoMenu)->draw(pJuego->getRender(), fondoRect);

	Estado::draw();
}

void Pausa::onInput(SDL_Event &e){

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			int i = 0;
			while (i < objetos.size())
			{
				objetos[i]->onInput(SuperNULL);
				i++;
			}

		}

	}

}