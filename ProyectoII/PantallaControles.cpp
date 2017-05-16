#include "PantallaControles.h"
#include "Boton.h"

PantallaControles::PantallaControles(Juego* pJ) : Menu(pJ)
{
	objetos.resize(1);
	initObjetos();
}
void PantallaControles::draw()const{
	Menu::draw();
}
static void goPlay(Juego * pj){

	pj->borraEstado = true;
	pj->estadoEnum = MundoReal;
};
void PantallaControles::initObjetos(){
	objetos[0] = new Boton(pJuego, 0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, TControles, ENull, goPlay);
}
PantallaControles::~PantallaControles()
{
}
