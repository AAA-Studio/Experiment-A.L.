
#include "GameOver.h"
#include "Boton.h"
#include <iostream>

GameOver::GameOver(Juego * pJ) : Menu(pJ)
{
	objetos.resize(1);
	cout << "estoy en gameover";
	initObjetos();
}


static void goMenu(Juego * pj){
	pj->borraEstado = true;
	pj->estadoEnum = MInicio;
};

void GameOver::initObjetos(){
	objetos[0] = new Boton(pJuego, 270, 150, TMenu, ENull, goMenu);
}

void GameOver::draw() const
{
	//SDL_Rect fondoRect = { 0, 0, pJuego->getAncho(), pJuego->getAlto() };
	//pJuego->getTextura(TFondoGameOver)->draw(pJuego->getRender(), fondoRect);

	Menu::draw();

}
