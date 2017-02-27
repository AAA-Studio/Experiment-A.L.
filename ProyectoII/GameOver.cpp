#include "GameOver.h"
#include "Boton.h"
#include <iostream>
#include "Menu.h"

GameOver::GameOver(Juego * pJ) : Estado(pJ)
{
	objetos.resize(1);
	initObjetos();
}


GameOver::~GameOver()
{
	
}

static void goMenu(Juego * pj){
	Menu * eMenu = new Menu(pj);
	pj->changeState(eMenu);
};

void GameOver::initObjetos(){
	objetos[0] = new Boton(pJuego, 270, 150, TMenu, ENull, goMenu);
}

void GameOver::draw() const
{
	//SDL_Rect fondoRect = { 0, 0, pJuego->getAncho(), pJuego->getAlto() };
	//pJuego->getTextura(TFondoGameOver)->draw(pJuego->getRender(), fondoRect);

	Estado::draw();

}

void GameOver::onInput(SDL_Event &e){

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