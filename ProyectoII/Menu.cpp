#include "Menu.h"
#include "Boton.h"


Menu::Menu(Juego * pJ) : Estado(pJ)
{
	objetos.resize(2);
	initObjetos();
}


Menu::~Menu()
{
}

void Menu::draw()const
{
	//SDL_Rect fondoRect = { 0, 0, pJuego->getAncho(), pJuego->getAlto() };
	//pJuego->getTextura(TFondoMenu)->draw(pJuego->getRender(), fondoRect);

	Estado::draw();
}

void Menu::initObjetos(){
	objetos[0] = new Boton(pJuego, 270, 250, TExit, ENull, goSalir);
	objetos[1] = new Boton(pJuego, 270, 150, TPlay, ENull, goPlay);
}

void Menu::onInput(SDL_Event &e){

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




