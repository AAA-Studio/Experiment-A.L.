#include "Pausa.h"
#include "Boton.h"

Pausa::Pausa(Juego * pJ) : Menu(pJ)
{
	initObjetos();
}

static void goPlay(Juego * pj){
	pj->popState();
};
static void goMenu(Juego * pj){
	pj->borraEstado = true;
	pj->estadoEnum = MInicio;
};

void Pausa::initObjetos(){
	objetos.push_back(new Boton(pJuego, 200, 400, 400, 100, JuegoSDL::TMenu, JuegoSDL::ENull, goMenu));
	objetos.push_back(new Boton(pJuego, 200, 200, 400, 100, JuegoSDL::TPlay, JuegoSDL::ENull, goPlay));
}