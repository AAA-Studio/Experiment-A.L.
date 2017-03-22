#include "Leer.h"
#include "Mundo.h"

Leer::Leer(Juego * pJ, Texturas_t textura) : Estado(pJ)
{
	text = textura;
	rect = { 20, 20, 600, 440 };
}

void Leer::draw()const {
	pJuego->getTextura(text)->draw(pJuego->getRender(), rect);//Dibujamos la textura
}

void Leer::update(){
	const Uint8 * keyStatesActuales = SDL_GetKeyboardState(NULL);
	if (keyStatesActuales[SDL_SCANCODE_V])
		pJuego->popState();
}
Leer::~Leer()
{
}
