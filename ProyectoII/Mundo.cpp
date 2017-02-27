#include "Mundo.h"
#include "GameOver.h"
#include "Pausa.h"
#include <typeinfo>
#include "Personaje.h"



Mundo::Mundo(Juego * pJ) : Estado(pJ)
{
	pJuego->setPausaFalse();

	objetos.resize(1);
	initObjetos();
	//pJuego->getMusica(MPlay)->play();
}


Mundo::~Mundo()
{
	
}

bool Mundo::colisionando(EntidadJuego * po1, EntidadJuego * po2){

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

void Mundo::onClick(){
	if (pJuego->getPausa())
	{
		Pausa * pausa = new Pausa(pJuego);
		pJuego->goToPausa(pausa);
	}
	else
		Estado::onClick();
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


