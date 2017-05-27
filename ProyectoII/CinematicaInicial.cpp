#include "CinematicaInicial.h"
#include <fstream>
using namespace std;
CinematicaInicial::CinematicaInicial(Juego * pJ, string mapa)
{
	pJuego = pJ;

	nivel = 0;
	indiceMapa = 1;

	pausa = false;

	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	this->mapa = new Mapa(this, mapa);
	initObjetos();

	cargaObjetos();

	psj->SetCinematica(true);

	contador = 0;
	objetos[0]->setVisible(false);
	moverI = false;
	dibuja = true;



}

void CinematicaInicial::cargaObjetos(){

	objetos.push_back(new Entidad(pJuego, 580 + 6, 800 + 40, 25, 25, JuegoSDL::TInforme1, JuegoSDL::ENull, OInforme1));//Informe

}

//Crea las texturas para los globos y todos los globos
void CinematicaInicial::initObjetos()
{
	psj = new Personaje(this, 320, 830, JuegoSDL::TJugador, JuegoSDL::ENull);
	
}

void CinematicaInicial::freeObjetos(){
	delete psj;
	psj = nullptr;

	for (size_t i = 0; i < objetos.size(); i++)//Se destruyen los objetos
	{
		delete(objetos[i]);
		objetos[i] = nullptr;
	}

}

void CinematicaInicial::update(){
	psj->update();//Update de personaje

		contador++;
		cinematicaInicial();
	
}

void CinematicaInicial::draw() const{
	if (dibuja)
	{

		//Render level
		//DIBUJAR MAPA
		mapa->draw();

		//Dibujar objetos del juego
	
		for (int i = objetos.size() - 1; i >= 0; i--)
			objetos[i]->draw(objetos[i]->getRect().x - camera.x, objetos[i]->getRect().y - camera.y);

		
		psj->draw(psj->getRect().x - camera.x, psj->getRect().y - camera.y);
		
		SDL_Rect a = getCamera();
		a.h = 200;
		a.w = 400;
		pJuego->getResources()->getTextura(JuegoSDL::TControles)->draw(pJuego->getRender(), a, 0, 0, nullptr);
		//pJuego->escribir("Pulsa ESPACIO para saltar",200, 200);
	}
}

void CinematicaInicial::cinematicaInicial(){

	//comienza la cinematica, el jugador se encuentra en la cama y se deja de dibujar
	if (contador == 400)
		dibuja = false;

	//se vuelve a dibujar, y aparece el jugador en el mundo oscuro
	if (contador == 500){
		setCamera(800 * 1, indiceMapa % 6 * 640);
		cambiaPosPSJ(1120, 830);
		dibuja = true;
	}

	//se deja de dibujar y se cambia al mundo real
	if (contador == 600)
	{
		dibuja = false;
		setCamera(0, indiceMapa % 6 * 640);
		cambiaPosPSJ(320, 830);
	}

	//se vuelve a dibujar, el jugador esta en la cama en el mundo real
	if (contador == 700)
	{
		dibuja = true;
	}

	if (contador == 800)
	{
		dibuja = false;
	}

	if (!dibuja && contador == 900){
		cambiaPosPSJ(360, 900);
		dibuja = true;
		moverI = true;
	}

	if (moverI && contador >= 1000){
		objetos[0]->setVisible(true);
		objetos[0]->move(0, 1);
	}

	if (objetos[0]->getRect().y >= 950){
		moverI = false;
		pJuego->setBorraEstado(true);
		pJuego->setEstadoEnum(MundoReal);
	}


}

CinematicaInicial::~CinematicaInicial()
{
	freeObjetos();
}

void CinematicaInicial::onInput(SDL_Event &e){
	if (e.type == SDL_KEYUP){ //si se pulsa una tecla comprueba que es p
		if (e.key.keysym.sym == SDLK_SPACE){
			pJuego->setBorraEstado(true);
			pJuego->setEstadoEnum(MundoReal);
		}
	}
}

