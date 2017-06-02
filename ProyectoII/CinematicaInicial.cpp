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
	comienzo = true;

	textoPsj.loadFromText(pJuego->getRender(), "Esa pesadilla me ha afectado demasiado, menudo dolor de cabeza.", { 255, 255, 255, 1 }, *pJuego->getResources()->getFuente(JuegoSDL::FNormal));
	textoSaltar.loadFromText(pJuego->getRender(), "Pulsa ESPACIO para saltar", { 255, 255, 255, 1 }, *pJuego->getResources()->getFuente(JuegoSDL::FNormal));

}

void CinematicaInicial::cargaObjetos(){

	objetos.push_back(new Entidad(pJuego, 580 + 6, 800 + 40, 25, 25, JuegoSDL::TInforme1, JuegoSDL::ENull, OInforme1));//Informe
	objetos.push_back(new Entidad(pJuego, 0, 750, 800, 500, JuegoSDL::TInvitacion, JuegoSDL::ENull, OInvitacion));//Invitacion


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

	if (comienzo)
	{
		objetos[1]->draw(objetos[1]->getRect().x - camera.x, objetos[1]->getRect().y - camera.y);
	}
	else if (dibuja)
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

		if (contador > 2200){
			pJuego->getResources()->getTextura(JuegoSDL::TControles)->draw(pJuego->getRender(), a, 0, pJuego->getWindowHeight() - 150, nullptr);
			textoPsj.renderFont(pJuego->getRender(), psj->getRect().x - camera.x - 150, psj->getRect().y - camera.y +70);
		}
	
		//pJuego->escribir("Pulsa ESPACIO para saltar",200, 200);
	}

	textoSaltar.renderFont(pJuego->getRender(), 0, 0);

}

void CinematicaInicial::cinematicaInicial(){
	if (contador == 1000)
		pJuego->getResources()->getEfecto(12)->play(0);


	if (contador == 1000){
		comienzo = false;
		objetos[1]->setVisible(false);

	}
	//comienza la cinematica, el jugador se encuentra en la cama y se deja de dibujar
	if (contador == 1100){
		dibuja = false;
		
	}

	//se vuelve a dibujar, y aparece el jugador en el mundo oscuro
	if (contador == 1200){
		pJuego->getResources()->getEfecto(10)->play(0);
		setCamera(800 * 1, indiceMapa % 6 * 640);
		cambiaPosPSJ(1120, 830);
		dibuja = true;
	}

	//se deja de dibujar y se cambia al mundo real
	if (contador == 1500)
	{
		dibuja = false;
		setCamera(0, indiceMapa % 6 * 640);
		cambiaPosPSJ(320, 830);
		objetos[1]->setVisible(false);
	}

	//se vuelve a dibujar, el jugador esta en la cama en el mundo real
	if (contador == 1600)
	{
		dibuja = true;
	}

	if (contador == 1700)
	{
		dibuja = false;
	}
	//Se mueve al personaje fuera de la cama
	if (contador == 1900){
		cambiaPosPSJ(360, 900);
		dibuja = true;
		moverI = true;
	}
	//Se desliza la carta
	if (moverI && contador >= 2000 && contador < 2100){
		objetos[0]->setVisible(true);
		objetos[0]->move(0, 1);
	}
	//El informe para y se pasa al estado mundo
	if (contador >2800){
		moverI = false;	

		pJuego->setBorraEstado(true);
		pJuego->setEstadoEnum(MundoReal);
	}
	if (contador > 2400){
		textoPsj.loadFromText(pJuego->getRender(), "Necesito tomarme las pastillas lo antes que pueda o me encontraré peor.", { 255, 255, 255, 1 }, *pJuego->getResources()->getFuente(JuegoSDL::FNormal));

	}
	if (contador > 2600)
		textoPsj.loadFromText(pJuego->getRender(), "Espera, ¿Y esa nota? ¿Quién la ha dejado ahí?", { 255, 255, 255, 1 }, *pJuego->getResources()->getFuente(JuegoSDL::FNormal));

}

CinematicaInicial::~CinematicaInicial()
{
	freeObjetos();
}

void CinematicaInicial::onInput(SDL_Event &e){
	if (e.type == SDL_KEYUP){ 
		if (e.key.keysym.sym == SDLK_SPACE && comienzo)
		{
			comienzo = false;
			contador = 999;
			objetos[1]->setVisible(false);

		}
		else if (e.key.keysym.sym == SDLK_SPACE){
			pJuego->setBorraEstado(true);
			pJuego->setEstadoEnum(MundoReal);
		}
	}
}

