#include "PantallaControles.h"
#include "Boton.h"

PantallaControles::PantallaControles(Juego* pJ) : Menu(pJ)
{
	objetos.resize(1);
	initObjetos();
}
void PantallaControles::draw()const{
	//Menu::draw();
	for (int i = objetos.size() - 1; i >= 0; i--)
		objetos[i]->draw(objetos[i]->getRect().x, objetos[i]->getRect().y);
}
static void goPlay(Juego * pj){

	pj->borraEstado = true;
	pj->estadoEnum = MundoReal;
};
void PantallaControles::initObjetos(){
	objetos[0] = new Boton(pJuego, 0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, TControles, ENull, goPlay);
}

void PantallaControles::onInput(SDL_Event &e){

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

void PantallaControles::update()
{
	for (int i = 0; i < objetos.size(); i++)
		objetos[i]->update();

}
PantallaControles::~PantallaControles()
{
}
