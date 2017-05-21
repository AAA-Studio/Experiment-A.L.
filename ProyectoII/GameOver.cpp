
#include "GameOver.h"
#include "Boton.h"
#include <iostream>

GameOver::GameOver(Juego * pJ) : Menu(pJ)
{
	objetos.resize(1);
	initObjetos();
}


static void goMenu(Juego * pj){
	pj->nuevoJuego = true;
	pj->borraEstado = true;
	pj->estadoEnum = MInicio;
};

void GameOver::initObjetos(){
	objetos[0] = new Boton(pJuego, 200, 200, 400, 100, JuegoSDL::TMenu, JuegoSDL::ENull, goMenu);
}

void GameOver::draw() const
{
	//SDL_Rect fondoRect = { 0, 0, pJuego->getAncho(), pJuego->getAlto() };
	//pJuego->getTextura(TFondoGameOver)->draw(pJuego->getRender(), fondoRect);

	Menu::draw();

}
