#include "Pausa.h"
#include "Boton.h"

Pausa::Pausa(Juego * pJ) : Menu(pJ)
{
	objetos.resize(2);
	initObjetos();
}


Pausa::~Pausa()
{
}

static void goPlay(Juego * pj){
	pj->popState();
};
static void goMenu(Juego * pj){
	pj->gestionaEstados(MInicio);
};

void Pausa::initObjetos(){
	objetos[0] = new Boton(pJuego, 270, 150, TMenu, ENull, goMenu);
	objetos[1] = new Boton(pJuego, 270, 250, TPlay, ENull, goPlay);

}

void Pausa::draw()const
{
	//SDL_Rect fondoRect = { 0, 0, pJuego->getAncho(), pJuego->getAlto() };
	//pJuego->getTextura(TFondoMenu)->draw(pJuego->getRender(), fondoRect);

	Menu::draw();
}
