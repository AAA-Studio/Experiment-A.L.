#include "GameOver.h"
#include "Boton.h"
#include <iostream>

GameOver::GameOver(Juego * pJ) : Menu(pJ)
{
	initObjetos();
}

static void goMenu(Juego * pj){
	//pj->nuevoJuego = true; //CAMBIAR
	pj->setBorraEstado(true);
	pj->setEstadoEnum(MInicio);
};
void GameOver::draw()const{
	//Dibujo fondo
	SDL_Rect rect = { 0, 0, pJuego->getWindowWidth(), pJuego->getWindowHeight() };
	pJuego->getResources()->getTextura(JuegoSDL::TFondoGameOver)->draw(pJuego->getRender(), rect, rect.x, rect.y, nullptr);

	//Dibujar objetos del juego
	for (int i = objetos.size() - 1; i >= 0; i--)
		objetos[i]->draw(objetos[i]->getRect().x, objetos[i]->getRect().y);
}
void GameOver::initObjetos(){
	objetos.push_back(new Boton(pJuego, 350, 150, 400, 100, JuegoSDL::TMenu, JuegoSDL::ENull, goMenu));
}