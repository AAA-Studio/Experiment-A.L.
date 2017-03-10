#include "MenuInicio.h"
#include "Boton.h"
#include "Mundo.h"


MenuInicio::MenuInicio(Juego * pJ) : Menu(pJ)
{
	objetos.resize(2);
	initObjetos();
}

void MenuInicio::draw()const
{
	//SDL_Rect fondoRect = { 0, 0, pJuego->getAncho(), pJuego->getAlto() };
	//pJuego->getTextura(TFondoMenu)->draw(pJuego->getRender(), fondoRect);

	Estado::draw();
}

static void goPlay(Juego * pj){

	Mundo * ePlay = new Mundo(pj);
	pj->changeState(ePlay);
};
static void goSalir(Juego * pj){
	pj->setSalir();
}

void MenuInicio::initObjetos(){
	objetos[0] = new Boton(pJuego, 270, 250, TExit, ENull, goSalir);
	objetos[1] = new Boton(pJuego, 270, 150, TPlay, ENull, goPlay);
}






