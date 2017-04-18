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
	mapa = new Mapa(this, m);
	initObjetos();

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
	// Personaje
	//Entidad de prueba para colisiones
	/*
	objetos.push_back(new Boton(pJuego, 500, 500, TPlay, ENull, goPlay));//Puerta
	objetos.push_back(new Entidad(pJuego, 200, 300, TInforme1, ENull, OInforme1));//Informe

	llaves.push_back(new Entidad(pJuego, 400, 300, TLlave, ENull, OLlave));//Llave
	*/
	//al principio del juego



	//HACER UN SWITCH
	int x = 0, y = 0;//Posiciones del jugador para cuando no encuentre el spawn

	x = mapa->getXSpawn();
	y = mapa->getYSpawn();
	psj = new Personaje(this, x, y, TJugador, ENull);

	enemigos.push_back(new Enemigo(pJuego, x + 100, y + 100, TPlay, ENull));


	//objetos.push_back (new Boton(pJuego, 0, 0, TPlay, ENull, goPlay));
}

void Mundo::freeObjetos(){
	delete psj;
	psj = nullptr;

	for (size_t i = 0; i < objetos.size(); i++)//Se destruyen los objetos
	{
		delete(objetos[i]);
		objetos[i] = nullptr;
	}

	list<Enemigo*>::iterator itEnemigo = enemigos.begin();
	while (!enemigos.empty() && itEnemigo != enemigos.end())//Se destruyen las llaves
	{
		delete(*itEnemigo);
		enemigos.erase(itEnemigo);
	}

	list<EntidadJuego*>::iterator itLlaves = llaves.begin();
	while (!llaves.empty() && itLlaves != llaves.end())//Se destruyen las llaves
	{
		delete(*itLlaves);
		llaves.erase(itLlaves);
	}

}


void Mundo::draw()const{

	//Render level
	//DIBUJAR MAPA
	mapa->draw();
	//Dibujar objetos del juego
	for (int i = objetos.size() - 1; i >= 0; i--)
		objetos[i]->draw();

	list<EntidadJuego*>::const_iterator it = llaves.cbegin();
	
	while (!llaves.empty() && it != llaves.cend())
	{
		(*it)->draw();
		it++;

	}

	list<Enemigo*>::const_iterator itEnemigos = enemigos.cbegin();
	while (!enemigos.empty() && itEnemigos != enemigos.cend())
	{
		(*itEnemigos)->draw();
		itEnemigos++;
	}

	psj->draw();

	pJuego->escribir("HOLA :)",50, 50);

}


void Mundo::update(){
	psj->update();//Update de personaje

	for (size_t i = 0; i < objetos.size(); i++)//Update de objetos
		objetos[i]->update();

	list<Enemigo*>::const_iterator citEnemigo = enemigos.cbegin();//Update de enemigos
	while (!enemigos.empty() && citEnemigo != enemigos.cend())
	{
		(*citEnemigo)->update();
		citEnemigo++;
	}

	list<EntidadJuego*>::const_iterator cit = llaves.cbegin();
	while (!llaves.empty() && cit != llaves.cend())//Update de las llaves
	{
		(*cit)->update();
		cit++;
	}



	//COLISIONES
	colBalaEnemigo();
	colBalaPersonaje();

	
}


void Mundo::colBalaEnemigo(){

	list <EntidadJuego*> balas = psj->getBalas();
	list<Enemigo*>::iterator itEnemigo = enemigos.begin();

	//Recorremos los enemigos
	while (!enemigos.empty() && itEnemigo != enemigos.cend())
	{
		list<EntidadJuego*>::iterator it = balas.begin();

		//Recorremos las balas
		while (!balas.empty() && it != balas.cend())
		{
			//Detectamos la colision de la bala con el enemigo
			if (checkCollision((*it)->getRect(), (*itEnemigo)->getRect()))
			{
				(*itEnemigo)->restaVida();
				psj->destruyeBala(*it);

				//Caso en el que el enemigo muere
				if ((*itEnemigo)->getVida() == 0)
				{
					list<Enemigo*>::iterator itAux = enemigos.begin();
					//Recorremos los enemigos para saber cual tiene que eliminarse
					while (itAux != enemigos.end() && (*itAux) != (*itEnemigo))
						itAux++;
					
					delete (*itAux);

					enemigos.erase(itAux);
				}
			}
			it++;
		}
		//Incrementamos el iterador si la lista de enemigos no está vacía
		if (!enemigos.empty())
			itEnemigo++;
	}
}


void Mundo::colBalaPersonaje(){

	list<Enemigo*>::const_iterator citEnemigo = enemigos.cbegin();

	//Colision balas con personaje 
	while (!enemigos.empty() && citEnemigo != enemigos.cend())
	{
		//Si el psj colisiona con el enemigo
		if (checkCollision(psj->getRect(), (*citEnemigo)->getRect())){
			//Se pide la hora y se compara con la última 
			if (SDL_GetTicks() - time >= duracion)
			{
				time = SDL_GetTicks();
				psj->restaVida();
				psj->empujeHaciaAtras();
			}

			if (psj->getVida() == 0){
				pJuego->borraEstado = true;
				pJuego->estadoEnum = MGameOver;
			}
		}
		citEnemigo++;
	}
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
	//psj->setCamera(mapa->getCamera());

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

EntidadJuego * Mundo::compruebaColisionObjetos(){
	size_t i = 0;
	
	while (i < objetos.size() && !checkCollision(psj->getRect(), objetos[i]->getRect()))
		i++;

	//Si lo he encontrado en los informes
	if (i != objetos.size())
		return objetos[i];

	//Si no, sigo buscando en la lista de llaves
	list<EntidadJuego*>::const_iterator it = llaves.cbegin();

	while (!llaves.empty() && it != llaves.cend() && !checkCollision(psj->getRect(),(*it)->getRect()))
	{
		it++;

	}

	if (it == llaves.cend())
		return nullptr;
	else
		return (*it);

}

void Mundo::destruyeLlave(EntidadJuego * llave)
{
	list<EntidadJuego*>::iterator it = llaves.begin();
	while (it != llaves.end() && (*it) != llave)//Recorre todas las llaves hasta encontrar la llave que tiene que destruir
	{
		it++;
	}

	//Elimina la llave
	llaves.erase(it);
	delete (llave);
	llave = nullptr;

	
	pJuego->setLlaveCogida(0);//Pone a true la llave a eliminar en el array de booleanos de las llaves de juego


}
