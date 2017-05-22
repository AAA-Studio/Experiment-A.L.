#include "Menu.h"

Menu::Menu(Juego * pJ) : pJuego(pJ){}

void Menu::onInput(SDL_Event &e){

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

void Menu::freeObjetos(){
	for (int i = 0; i < objetos.size(); i++)
	{
		delete(objetos[i]);
		objetos[i] = nullptr;
	}
}

void Menu::update()
{
	for (int i = 0; i < objetos.size(); i++)
		objetos[i]->update();

}

void Menu::draw() const
{
	//Dibujo fondo
	SDL_Rect rect = { 0, 0, pJuego->getWindowWidth(), pJuego->getWindowHeight() };
	pJuego->getResources()->getTextura(JuegoSDL::TFondo)->draw(pJuego->getRender(), rect, rect.x, rect.y, nullptr);

	//Dibujar objetos del juego
	for (int i = objetos.size() - 1; i >= 0; i--)
		objetos[i]->draw(objetos[i]->getRect().x,objetos[i]->getRect().y);

}