#include "GameOver.h"
#include "Boton.h"
#include <iostream>

GameOver::GameOver(Juego * pJ) : Menu(pJ)
{
	initObjetos();
}

static void goMenu(Juego * pj){
	pj->nuevoJuego = true;
	pj->borraEstado = true;
	pj->estadoEnum = MInicio;
};

void GameOver::initObjetos(){
	objetos.push_back(new Boton(pJuego, 200, 200, 400, 100, JuegoSDL::TMenu, JuegoSDL::ENull, goMenu));
}