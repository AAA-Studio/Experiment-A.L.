#include "Mundo.h"
#include <typeinfo>
#include "Personaje.h"
#include <iostream>
#include <SDL.h>
#include "Bala.h"
#include "Boton.h"


Mundo::Mundo(Juego * pJ, string m)
{
	pJuego = pJ;
	pausa = false;
	objetos.resize(1);
	initObjetos();
	mapa = new Mapa(pJ, this, m);
	//pJuego->getMusica(MPlay)->play();
}


Mundo::~Mundo()
{
	freeObjetos();

}

static void goPlay(Juego * pj){

};

//Crea las texturas para los globos y todos los globos
void Mundo::initObjetos()
{
	int x = 0, y = 0;//Posiciones del globo

	if (pJuego->getNivel() == 1){
		// Personaje
		mapa-> buscaSpawn(100, x, y);
		psj = new Personaje(pJuego, x, y, TJugador, ENull);
	}
	//Entidad de prueba para colisiones
	objetos[0] = new Boton(pJuego, 500, 500, TPlay, ENull, goPlay);
}

void Mundo::freeObjetos(){
	delete psj;
	psj = nullptr;

	for (size_t i = 0; i < objetos.size(); i++)
	{
		delete(objetos[i]);
		objetos[i] = nullptr;
	}
}


void Mundo::draw()const{

	//Render level
	//DIBUJAR MAPA
	mapa->draw();
	//Dibujar objetos del juego
	for (int i = objetos.size() - 1; i >= 0; i--)
		objetos[i]->draw();

	psj->draw();

	pJuego->getTextura(TFuente)->render(pJuego->getRender(), 0, 0, "Hola", pJuego->getFuente());

}


void Mundo::update(){
	psj->update();
	for (size_t i = 0; i < objetos.size(); i++)
		objetos[i]->update();

	/*if (checkCollision(psj->getRect(), objetos[0]->getRect())){//Si el psj colisiona con el boton truleano
		pJuego->indiceMapas = 1;
		pJuego->borraEstado = true;
		pJuego->estadoEnum = MundoReal;


	}

	//AQUI AÑADIREMOS LOS DIFERENTES CASOS DEPENDIENDO DE LA ALFOMBRILLA.
	/*if (checkCollision(psj->getRect(), objetos[1]->getRect())){
		pJuego->indiceMapas = 2;
		pJuego->borraEstado = true;
		pJuego->estadoEnum = MundoReal;


	}
	*/
}

//Detecta el input del jugador y la pausa
void Mundo::onInput(SDL_Event &e){
	
	//Declaramos el array con los estados de teclado
	const Uint8 * keyStatesActuales = SDL_GetKeyboardState(NULL);
	
	//Pausa
	if (keyStatesActuales[SDL_SCANCODE_ESCAPE]){
		pJuego->borraEstado = true;
		pJuego->estadoEnum = MPausa;
	}
	
	//Personaje
	psj->onInput();
	psj->setCamera(mapa->getCamera());

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