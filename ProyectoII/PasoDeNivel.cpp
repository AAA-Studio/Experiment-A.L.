#include "PasoDeNivel.h"


PasoDeNivel::PasoDeNivel(Juego * pJ) : Menu(pJ)
{
	time = timeAnim = SDL_GetTicks();

	rect = { 250, 100, 300, 400 };
	textRect = {
		0,
		3 * (pJuego->getResources()->getTextura(JuegoSDL::Texturas_t::TPuerta)->getH() + 10) / 4,
		pJuego->getResources()->getTextura(JuegoSDL::Texturas_t::TPuerta)->getW(),
		(pJuego->getResources()->getTextura(JuegoSDL::Texturas_t::TPuerta)->getH() + 10) / 4 
	};

	initObjetos();
	//pJ->getResources()->getEfecto(JuegoSDL::Efectos_t::EPuerta)->play();
}

void PasoDeNivel::initObjetos(){

}

void PasoDeNivel::update(){
	if (SDL_GetTicks() - time >= duracion)
	{
		pJuego->popState();
	}
	if (SDL_GetTicks() - timeAnim >= duracionAnim)
	{
		timeAnim = SDL_GetTicks();
		textRect.y -= textRect.h;
	}


}

void PasoDeNivel::draw() const
{
	pJuego->getResources()->getTextura(JuegoSDL::Texturas_t::TPuerta)->draw(pJuego->getRender(), rect, rect.x, rect.y, &textRect);
}

