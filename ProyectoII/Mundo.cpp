#include "Mundo.h"
#include "GameOver.h"
#include "Pausa.h"
#include <typeinfo>
#include "Personaje.h"



Mundo::Mundo(Juego * pJ) : Estado(pJ)
{
	pausa = false;

	objetos.resize(1);
	initObjetos();
	//pJuego->getMusica(MPlay)->play();
}


Mundo::~Mundo()
{
	
}


//Crea las texturas para los globos y todos los globos
void Mundo::initObjetos()
{
	int x = 0, y = 0;//Posiciones del globo
	x = rand() % (pJuego->getAncho() - 100);
	y = rand() % (pJuego->getAlto() - 100);
	// Personaje
	objetos[0] = new Personaje(pJuego, x, y, TJugador, ENull);

}



void Mundo::draw()const{

	//SDL_Rect fondoRect = { 0, 0, pJuego->getAncho(), pJuego->getAlto() };
	//pJuego->getTextura(TFondo)->draw(pJuego->getRender(), fondoRect);

	//Dibujar objetos del juego
	Estado::draw();

	pJuego->getTextura(TFuente)->render(pJuego->getRender(), 0, 0, "Hola", pJuego->getFuente());

}

void Mundo::update(){
	Estado::update();
}

void Mundo::onInput(SDL_Event &e){

	if (e.type == SDL_KEYUP)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE){
			Pausa * pausa = new Pausa(pJuego);
			pJuego->goToPausa(pausa);
		}
		else if (e.key.keysym.sym == SDLK_w)
		{
			objetos[0]->onInput(JArriba);

		}
		else if (e.key.keysym.sym == SDLK_a)
		{
			objetos[0]->onInput(JIzquierda);

		}
		else if (e.key.keysym.sym == SDLK_s)
		{
			objetos[0]->onInput(JAbajo);

		}
		else if (e.key.keysym.sym == SDLK_d)
		{
			objetos[0]->onInput(JDerecha);

		}

	}

}


//Globo y premio
// Los objetos informarán al juego cuando causen baja
void Mundo::newBaja(EntidadJuego* po)
{
	/*if (typeid(*po) == typeid(Premio))
		dynamic_cast<Premio*> (po)->reiniciar();

	else
	{
		contGlobos--;
		if (contGlobos == 0)
		{
			GameOver *go = new GameOver(pJuego, puntosTotales);
			pJuego->changeState(go);
		}
	}*/
}


