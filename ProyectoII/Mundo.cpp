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
	cargaObjetos();
	abierto = false;
	balaDestruida = false;
	//cerraduras[0] = false;
	//puertas[0] = 0;

	//pJuego->getMusica(MPlay)->play();
}


Mundo::~Mundo()
{
	freeObjetos();

}
void Mundo::cargaObjetos(){
	string objts = pJuego->dameObjetos();
	int nivel = pJuego->indiceMapas;
	std::ifstream obj(objts);
	if (!obj.is_open())
	{
		printf("Unable to load map file!\n");
	}
	bool hecho = false;
	string nombre;
	int i = 1;
	while (obj.peek() != EOF && !hecho){


		if (i == 1)
			obj >> nombre;

		int y, x,w,h, lvl;
		if (nombre == "NIVEL"){

			obj >> lvl;

			if (nivel == lvl){

				obj >> nombre;

				while (obj.peek() != EOF && nombre != "NIVEL"){
					if (nombre == "LLAVE"){
						obj >> x >> y>> w >> h;
						llaves.push_back(new Entidad(pJuego, x, y,w,h, TLlave, ENull, OLlave));
					}
					else if (nombre == "PANEL"){

						obj >> x >> y >> w >> h;
						objetos.push_back(new Entidad(pJuego, x, y,w,h, TTeclado, ENull, OTeclado));
					}
					else if (nombre == "ENEMIGO"){

						obj >> x >> y >> w >> h;
						enemigos.push_back(new Enemigo(this, x, y, w, h, TLeon, ENull));

					}

					obj >> nombre;

				}

				hecho = true;
			}
			else{
				obj >> nombre;
				while (obj.peek() != EOF && nombre != "NIVEL"){
					if (nombre == "LLAVE"){
						obj >> x >> y >> w >> h;
					}
					else if (nombre == "ENEMIGO"){
						obj >> x >> y >> w >> h;
					}
					else if (nombre == "PANEL"){
						obj >> x >> y >> w >> h;
					}
					obj >> nombre;
				}
			}
		}
		i++;
	}
	obj.close();
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

	
	*/
	//al principio del juego



	//HACER UN SWITCH
	int x = 0, y = 0;//Posiciones del jugador para cuando no encuentre el spawn

		x = mapa->getXSpawn();
		y = mapa->getYSpawn();
		psj = new Personaje(this, x, y, TJugador, ENull);
		//objetos.push_back(new Entidad(pJuego, 350, 300, TTeclado, ENull, OTeclado));
		//llaves.push_back(new Entidad(pJuego, 400, 300, TLlave, ENull, OLlave));//Llave
			//enemigos.push_back(new Enemigo(this, x + 100, y + 100, TLeon, ENull));


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
		while (!enemigos.empty() && itEnemigo != enemigos.end())
		{
			delete(*itEnemigo);
			itEnemigo = enemigos.erase(itEnemigo);
		}

		list<EntidadJuego*>::const_iterator it = llaves.cbegin();
		for (; it != llaves.cend() && llaves.empty(); it++){
			destruyeLlave(*it);
		}

		//Balas
		list<EntidadJuego*>::iterator itBalasPsj = balasPsj.begin();
		while (!balasPsj.empty() && itBalasPsj != balasPsj.end())
		{
			delete(*itBalasPsj);
			itBalasPsj = balasPsj.erase(itBalasPsj);
		}

		list<EntidadJuego*>::iterator itBalasEnem = balasEnems.begin();
		while (!balasEnems.empty() && itBalasEnem != balasEnems.end())
		{
			delete(*itBalasEnem);
			itBalasEnem = balasEnems.erase(itBalasEnem);
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

		//Balas
		list<EntidadJuego*>::const_iterator itBalasPsj = balasPsj.cbegin();
		while (!balasPsj.empty() && itBalasPsj != balasPsj.cend())
		{
			(*itBalasPsj)->draw();
			itBalasPsj++;
		}

		list<EntidadJuego*>::const_iterator itBalasEnem = balasEnems.cbegin();
		while (!balasEnems.empty() && itBalasEnem != balasEnems.cend())
		{
			(*itBalasEnem)->draw();
			itBalasEnem++;
		}


		//pJuego->escribir("HOLA :)",50, 50);
	}


	void Mundo::update(){
		psj->update();//Update de personaje
		balaDestruida = false;
		//Balas
		list<EntidadJuego*>::const_iterator itBalasPsj = balasPsj.cbegin();
		while (!balaDestruida && !balasPsj.empty() && itBalasPsj != balasPsj.cend())
		{
			balaDestruida = false;
			(*itBalasPsj)->update();
			if (!balaDestruida)//Si no ha sido destruida en el update, avanzo
				itBalasPsj++;
			else
				itBalasPsj = balasPsj.erase(itBalasPsj);

		}

		list<EntidadJuego*>::iterator itBalasEnem = balasEnems.begin();
		while (!balaDestruida && !balasEnems.empty() && itBalasEnem != balasEnems.end())
		{
			balaDestruida = false;
			(*itBalasEnem)->update();
			if (!balaDestruida)//Si no ha sido destruida en el update, avanzo
				itBalasEnem++;
			else
				itBalasEnem = balasEnems.erase(itBalasEnem);
		}

		list<Enemigo*>::const_iterator citEnemigo = enemigos.cbegin();//Update de enemigos
		while (!enemigos.empty() && citEnemigo != enemigos.cend())
		{
			(*citEnemigo)->update();
			citEnemigo++;
		}


		for (size_t i = 0; i < objetos.size(); i++)//Update de objetos
			objetos[i]->update();


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

		list<Enemigo*>::iterator itEnemigo = enemigos.begin();

		//Recorremos los enemigos
		while (!enemigos.empty() && itEnemigo != enemigos.cend())
		{
			list<EntidadJuego*>::iterator it = balasPsj.begin();

			//Recorremos las balas
			while (!balasPsj.empty() && it != balasPsj.cend())
			{
				//Detectamos la colision de la bala con el enemigo
				if (checkCollision((*it)->getRect(), (*itEnemigo)->getRect()))
				{
					(*itEnemigo)->restaVida();
					destruyeBala(balasPsj, it);

					//Caso en el que el enemigo muere
					if ((*itEnemigo)->getVida() == 0)
					{
						//Recorremos los enemigos para saber cual tiene que eliminarse
						delete (*itEnemigo);
						itEnemigo = enemigos.erase(itEnemigo);
					}
				}
				else
					it++;
			}
			//Incrementamos el iterador si la lista de enemigos no está vacía
			if (!enemigos.empty())
				itEnemigo++;
		}
	}


	void Mundo::colBalaPersonaje(){

		list<EntidadJuego*>::iterator itBalasEnems = balasEnems.begin();

		//Colision balas con personaje 
		while (!balasEnems.empty() && itBalasEnems != balasEnems.end())
		{
			//Si el psj colisiona con el enemigo
			if (checkCollision(psj->getRect(), (*itBalasEnems)->getRect())){
				//Se pide la hora y se compara con la última 
				if (SDL_GetTicks() - time >= duracion)
				{
					time = SDL_GetTicks();
					psj->restaVida();
				}

				destruyeBala(balasEnems, itBalasEnems);

				if (psj->getVida() == 0){
					pJuego->borraEstado = true;
					pJuego->estadoEnum = MGameOver;
				}
			}
			else
				itBalasEnems++;
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
		compruebaPersonaje();
		//psj->setCamera(mapa->getCamera());

	}
	void Mundo::compruebaPersonaje(){
		SDL_Rect rect, rect2;

		int x, y;

		rect.x = psj->getX();
		rect.y = psj->getY();

		rect2.x = psj->DamePosAntX();
		rect2.y = psj->DamePosAntY();

		rect2.w = rect.w = rect2.h = rect.h = 20;

		x = rect.x - rect2.x;
		y = rect.y - rect2.y;


		Direccion dir;
		dir.x = x;
		dir.y = y;
		psj->setDir(dir);

		//comprueba la X
		if (mapa->touchesWall(rect)){
			rect.x -= x;
		}
		// comprueba la Y
		if (mapa->touchesWall(rect)){
			rect.y -= y;
		}

		psj->setPosChocando(rect.x, rect.y);

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

		while (!llaves.empty() && it != llaves.cend() && !checkCollision(psj->getRect(), (*it)->getRect()))
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
		it = llaves.erase(it);
		delete (llave);
		llave = nullptr;


		pJuego->setLlaveCogida(0);//Pone a true la llave a eliminar en el array de booleanos de las llaves de juego


	}

	void Mundo::destruyeBala(list <EntidadJuego*> & lista, list<EntidadJuego*>::iterator & it)
	{
		delete (*it);
		it = lista.erase(it);
		balaDestruida = true;
	}

	void Mundo::insertaBala(ListaBalas_t lista, EntidadJuego * bala)
	{
		if (lista == LBalasPersonaje)
			balasPsj.push_back(bala);

		else
			balasEnems.push_back(bala);

	}
