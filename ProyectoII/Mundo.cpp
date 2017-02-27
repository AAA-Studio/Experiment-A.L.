#include "Mundo.h"
#include "GameOver.h"
#include "Pausa.h"
#include <typeinfo>
#include "Personaje.h"
#include <iostream>
#include <SDL.h>
#include "Bala.h"


Mundo::Mundo(Juego * pJ) : Estado(pJ)
{
	pausa = false;
	objetos.resize(2);
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

	objetos[1] = new Bala(pJuego, 0, 0, TPlay, ENull);

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
	
	//Declaramos el array con los estados de teclado
	const Uint8 * keyStatesActuales = SDL_GetKeyboardState(NULL);
	
	if (keyStatesActuales[SDL_SCANCODE_ESCAPE]){
			Pausa * pausa = new Pausa(pJuego);
			pJuego->goToPausa(pausa);
	}
	else if (keyStatesActuales[SDL_SCANCODE_W] && keyStatesActuales[SDL_SCANCODE_A])
		objetos[0]->onInput(WA);

	else if (keyStatesActuales[SDL_SCANCODE_W] && keyStatesActuales[SDL_SCANCODE_D])
		objetos[0]->onInput(WD);

	else if (keyStatesActuales[SDL_SCANCODE_S] && keyStatesActuales[SDL_SCANCODE_A])
		objetos[0]->onInput(SA);

	else if (keyStatesActuales[SDL_SCANCODE_S] && keyStatesActuales[SDL_SCANCODE_D])
		objetos[0]->onInput(SD);

	else if (keyStatesActuales[SDL_SCANCODE_W])
			objetos[0]->onInput(W);
		
	else if (keyStatesActuales[SDL_SCANCODE_A])
			objetos[0]->onInput(A);

	else if (keyStatesActuales[SDL_SCANCODE_S])
		objetos[0]->onInput(S);
		
	else if (keyStatesActuales[SDL_SCANCODE_D])
		objetos[0]->onInput(D);
	if (keyStatesActuales[SDL_SCANCODE_E])
		objetos[0]->onInput(JPIUM);
		
	
	//objetos[0]->onInput(pila);


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

void Mundo::newBala(EntidadJuego* po)
{
	int x, y, ang;
	x = static_cast<Personaje*> (po)->getX();
	y = static_cast<Personaje*> (po)->getY();
	ang = static_cast<Personaje*> (po)->getAngulo();

	static_cast<Bala*> (objetos[1])->setPos(x, y);
	static_cast<Bala*> (objetos[1])->setAngulo(ang);

}

bool Mundo::colisionando(EntidadJuego* po1, EntidadJuego* po2){
	SDL_Rect rectA, rectB;
	rectA = po1->dameRect();
	rectB = po2->dameRect();
	
		if ((rectA.y + rectA.h) <= rectB.y)
		{
		return false;
		}
	
		if (rectA.y >= (rectB.y + rectB.h))
		{
		return false;
		}
	
		if ((rectA.x + rectA.w) <= rectB.x)
		{
		return false;
		}
	
		if (rectA.x >= (rectB.x + rectB.w))
		{
		return false;
		}
	
			//If none of the sides from A are outside B
		return true;
	
}


