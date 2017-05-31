#include "MenuInicio.h"
#include "Boton.h"


MenuInicio::MenuInicio(Juego * pJ) : Menu(pJ)
{
	initObjetos();

	pJ->getResources()->getMusica(JuegoSDL::MInicio)->play();
}

static void goControles(Juego * pj){
	pj->setBorraEstado(true);
	pj->setEstadoEnum (CinematicaI);
};
static void goSalir(Juego * pj){
	pj->setSalir();
}

void MenuInicio::initObjetos(){
	objetos.push_back(new Boton(pJuego, 40, 300, 300, 70, JuegoSDL::TExit, JuegoSDL::ENull, goSalir));
	objetos.push_back(new Boton(pJuego, 40, 150, 300, 70, JuegoSDL::TPlay, JuegoSDL::ENull, goControles));
}









