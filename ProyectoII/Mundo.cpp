#include "Mundo.h"
#include "GameOver.h"
#include "Pausa.h"
#include <typeinfo>
#include "Personaje.h"
#include <iostream>
#include <SDL.h>
#include "Bala.h"
#include "Boton.h"


Mundo::Mundo(Juego * pJ) : Estado(pJ)
{
	pausa = false;
	objetos.resize(2);
	initObjetos();
	mapa = new Mapa(pJ);
	//pJuego->getMusica(MPlay)->play();
}


Mundo::~Mundo()
{


}

static void goPlay(Juego * pj){

};

//Crea las texturas para los globos y todos los globos
void Mundo::initObjetos()
{
	int x = 0, y = 0;//Posiciones del globo
	x = rand() % (pJuego->getAncho() - 100);
	y = rand() % (pJuego->getAlto() - 100);
	// Personaje
	objetos[0] = new Personaje(pJuego, x, y, TJugador, ENull);

	//Entidad de prueba para colisiones
	objetos[1] = new Boton(pJuego, 500, 500, TPlay, ENull, goPlay);
}


void Mundo::draw()const{

	//SDL_Rect fondoRect = { 0, 0, pJuego->getAncho(), pJuego->getAlto() };
	//pJuego->getTextura(TFondo)->draw(pJuego->getRender(), fondoRect);
	//Render level
	//DIBUJAR MAPA
	mapa->draw();
	//Dibujar objetos del juego
	Estado::draw();

	pJuego->getTextura(TFuente)->render(pJuego->getRender(), 0, 0, "Hola", pJuego->getFuente());

}


void Mundo::update(){
	Estado::update();
	if (checkCollision(static_cast<Entidad*>(objetos[0])->getRect(), static_cast<Entidad*>(objetos[1])->getRect()))//Si el psj colisiona con el boton truleano
		static_cast<Personaje*> (objetos[0])->restaVida();
}

void Mundo::onInput(SDL_Event &e){
	
	//Declaramos el array con los estados de teclado
	const Uint8 * keyStatesActuales = SDL_GetKeyboardState(NULL);
	
	if (keyStatesActuales[SDL_SCANCODE_ESCAPE]){
			Pausa * pausa = new Pausa(pJuego);
			pJuego->goToPausa(pausa);
	}

	objetos[0]->onInput();
	static_cast<Personaje*>(objetos[0])->setCamera(mapa->getCamera());

}


//Globo y premio
// Los objetos informarán al juego cuando causen baja
void Mundo::newBaja(EntidadJuego* po)
{
	GameOver *go = new GameOver(pJuego);
	pJuego->changeState(go);
}

bool Mundo::checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	return !(bottomA <= topB || topA >= bottomB || rightA <= leftB || (leftA >= rightB));

}