#include "Mundo.h"
#include <typeinfo>
#include "Personaje.h"
#include <iostream>
#include <SDL.h>
#include "Bala.h"
#include <fstream>
#include "EnemigoIA.h"

//Metodos ordenadiiiiiiiiiiiiiisimos :D

Mundo::Mundo(Juego * pJ, string m)
{
	pJuego = pJ;
	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	psj = nullptr;
	mundo = MReal;

	//Mapa
	nivel = 0;
	indiceMapa = 1;
	mapa = new Mapa(this, m);

	initObjetos();
	cargaObjetos();

	balaDestruida = false;
	//pausa = false;
	//abierto = false;
	//cerraduras[0] = false;
	//puertas[0] = 0;

	pasoNivel = false;
	//HABRA QUE QUITAR ESTOOOOOOOOOOOOOOOOOO
	cinematica = false;
	contador = 0;
	//objetos[1]->setVisible(false);
	moverI = false;
	moverP = false;
	dibuja = true;
	veces = 0;
	primeCinematica = true;
	pJuego->getResources()->getMusica(JuegoSDL::Musica_t::MReal)->play();

	psj->empiezaPerderVida();

	for (int i = 0; i < TAMAÑO_LLAVES; i++) //Se inicializan las llaves
		llavesCogidas[i] = false;

	alfo = 0;
	pJuego->getResources()->getTextura(JuegoSDL::TNegro)->setAlpha(alfo);
	nivelCambiado = false;
}
Mundo::~Mundo()
{
	freeObjetos();

}

//Objetos
void Mundo::cargaObjetos(){
	string objts = pJuego->getNombreObjetos();


	std::ifstream obj(objts);
	if (!obj.is_open())
	{
		printf("Unable to load map file!\n");
	}
	string nombre;
	int i = 1;
	int y, x, w, h, lvl, tipo, ancho, alto;
	alto = 640;
	while (obj.peek() != EOF){


		if (i == 1)
			obj >> nombre;


		int cadencia,balas;
		if (nombre == "NIVEL"){

			obj >> lvl;
			obj >> nombre;

			if (lvl < 6)
				ancho = 0;
			else
				ancho = 800;


			while (obj.peek() != EOF && nombre != "NIVEL"){
				if (nombre == "LLAVE"){
					obj >> x >> y >> w >> h;
					llaves.push_back(new Entidad(pJuego, x + ancho*lvl, y + alto*lvl, w, h, JuegoSDL::TLlave, JuegoSDL::ENull, OLlave));
				}
				else if (nombre == "INFORME"){
					obj >> x >> y >> w >> h >> tipo;
					if (tipo == 1)
						objetos.push_back(new Entidad(pJuego, 580 + ancho*lvl, 220 + alto*lvl, w, h, JuegoSDL::TInforme1, JuegoSDL::ENull, OInforme1));//Informe
						
					else if (tipo == 2)
						objetos.push_back(new Entidad(pJuego, x + ancho*lvl, y + alto*lvl, w, h, JuegoSDL::TInforme2, JuegoSDL::ENull, OInforme2));//Informe
				}
				else if (nombre == "PANEL"){

					obj >> x >> y >> w >> h;
					objetos.push_back(new Entidad(pJuego, x + ancho*lvl, y + alto*lvl, w, h, JuegoSDL::TTeclado, JuegoSDL::ENull, OTeclado));
				}
				else if (nombre == "ARMA"){

					obj >> x >> y >> w >> h >> balas >> cadencia;
					armas.push_back(new Armas(pJuego, x + ancho*lvl, y + alto*lvl, w, h, balas, cadencia, JuegoSDL::TPistola, JuegoSDL::ENull, OPistola));
				}
				else if (nombre == "ENEMIGO"){

					obj >> x >> y >> w >> h;
					enemigos.push_back(new Enemigo(this, x + ancho*lvl, y + alto*lvl, w, h, JuegoSDL::TLeon, JuegoSDL::ENull));

				}

				obj >> nombre;

			}
		}
		i++;
	}
	obj.close();
}
void Mundo::initObjetos()
{
	//lala
		if (primeCinematica)
		{
			psj = new Personaje(this, 400, 830, JuegoSDL::TJugador, JuegoSDL::ENull);
			vector < pair<float, float>> waypoints;
			waypoints.push_back(make_pair(450, 840));
			waypoints.push_back(make_pair(450, 1200));
			waypoints.push_back(make_pair(700, 1000));

			enemigosIA.push_back(new EnemigoIA(this, psj, 400, 830, 100, 100, JuegoSDL::TLeon, JuegoSDL::ENull, waypoints));
		}
		else
		{
			int x = 0, y = 0;//Posiciones del jugador para cuando no encuentre el spawn

			x = mapa->getXSpawn();
			y = mapa->getYSpawn();
			psj = new Personaje(this, x, y, JuegoSDL::TJugador, JuegoSDL::ENull);

		}
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

		list<EnemigoIA*>::iterator itEnemigoIA = enemigosIA.begin();
		while (!enemigosIA.empty() && itEnemigoIA != enemigosIA.end())
		{
			delete(*itEnemigoIA);
			itEnemigoIA = enemigosIA.erase(itEnemigoIA);
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

		list<Armas*>::iterator itArmas = armas.begin();
		while (!armas.empty() && itArmas != armas.end())
		{
			delete(*itArmas);
			itArmas = armas.erase(itArmas);
		}

	}

void Mundo::draw()const{

		if (dibuja)
		{
			//DIBUJAR MAPA
			mapa->draw();

			//Dibujar objetos del juego
			//Armas
			for (auto arma : armas)
				arma->draw(arma->getRect().x - camera.x, arma->getRect().y - camera.y);

			for (auto objeto: objetos)
				objeto->draw(objeto->getRect().x - camera.x, objeto->getRect().y - camera.y);
				
			for (auto llave : llaves)
				llave->draw(llave->getRect().x - camera.x, llave->getRect().y - camera.y);

			for (auto enemigo : enemigos)
				enemigo->draw(enemigo->getRect().x - camera.x, enemigo->getRect().y - camera.y);

			for (auto enemigoIA : enemigosIA)
				enemigoIA->draw(enemigoIA->getRect().x - camera.x, enemigoIA->getRect().y - camera.y);

			psj->draw(psj->getRect().x - camera.x, psj->getRect().y - camera.y);
	
			//Balas personaje
			for (auto bala : balasPsj) 
				bala->draw(bala->getRect().x - camera.x, bala->getRect().y - camera.y);
			
			//Balas enemigo
			for (auto bala : balasEnems) 
				bala->draw(bala->getRect().x - camera.x, bala->getRect().y - camera.y);
			
			//Dibujo sangre
			pJuego->getResources()->getTextura(JuegoSDL::TBlood)->setAlpha(255 - psj->getAlpha());
			pJuego->getResources()->getTextura(JuegoSDL::TBlood)->draw(pJuego->getRender(), psj->getHUD(), 0, 0, nullptr);

			//Dibujo controles
			SDL_Rect a = getCamera();
			a.h = 200;
			a.w = 400;
			pJuego->getResources()->getTextura(JuegoSDL::TControles)->draw(pJuego->getRender(), a, 0, 0, nullptr);
			
			//pJuego->escribir("¿Y esa nota?", pJuego->getWindowWidth()/2, pJuego->getWindowHeight()/2);
			//Dibujar fondo negro

			a.h = 640;
			a.w = 800;
			if (pasoNivel || nivelCambiado){
				pJuego->getResources()->getTextura(JuegoSDL::TNegro)->setAlpha(alfo);		
			}
			pJuego->getResources()->getTextura(JuegoSDL::TNegro)->draw(pJuego->getRender(), a, 0, 0, nullptr);

		}
	}
void Mundo::update(){
		psj->update();//Update de personaje
		balaDestruida = false;

		//Caso GameOver
		if (psj->getVida() <= 0){
			pJuego->setEstadoEnum(MGameOver);
			pJuego->setBorraEstado(true);
		}

		//Balas personaje
		list<EntidadJuego*>::const_iterator itBalasPsj = balasPsj.cbegin();
		while (!balaDestruida && !balasPsj.empty() && itBalasPsj != balasPsj.cend())
		{
			balaDestruida = false;
			if (checkCollision(camera, (*itBalasPsj)->getRect())){
				(*itBalasPsj)->update();
				if (!balaDestruida && mapa->touchesWall((*itBalasPsj)->getRect())){
					delete (*itBalasPsj);
					itBalasPsj = balasPsj.erase(itBalasPsj);
					balaDestruida = true;
				}
				else
					itBalasPsj++;
			}
			else
				itBalasPsj++;
		}

		//Balas enemigo
		list<EntidadJuego*>::iterator itBalasEnem = balasEnems.begin();
		while (!balaDestruida && !balasEnems.empty() && itBalasEnem != balasEnems.end())
		{
			if (checkCollision(camera, (*itBalasEnem)->getRect())){
				balaDestruida = false;
				(*itBalasEnem)->update();
				if (!balaDestruida)//Si no ha sido destruida en el update, avanzo
					itBalasEnem++;
				else
					itBalasEnem = balasEnems.erase(itBalasEnem);
			}
			else
				itBalasEnem++;
		}

		//Enemigos
		for (auto enemigo : enemigos){
			if (checkCollision(camera, enemigo->getRect()))
				enemigo->update();
		}
		for (auto enemigoIA : enemigosIA){
			if (checkCollision(camera, enemigoIA->getRect()))
				enemigoIA->update();
		}

		//Update de objetos
		for (auto obj : objetos){
			if (checkCollision(camera, obj->getRect()))
				obj->update();
		}
			
		//Update de las llaves
		for (auto llave : llaves){
			if (checkCollision(camera, llave->getRect()))
				llave->update();			
		}

		//COLISIONES
		colBalaEnemigo();
		colBalaPersonaje();
		
		if (cinematica)
		{
			contador++;
			//cinematicaInicial();
		}
		if (pasoNivel){
			alfo += 10;
			if (alfo > 255){			
				pasoNivel = false;
				nivelCambiado = true;
				mapa->buscaSpawn();

			}
			
		}
		if (nivelCambiado){
			alfo -= 10;
			if(alfo ==0)//Se pide la hora y se compara con la última 
			{
				alfo = 0;
				nivelCambiado = false;
			}
		}

	}
void Mundo::onInput(SDL_Event &e){

		if (!nivelCambiado && !pasoNivel) // NO PLS
		{
			//Declaramos el array con los estados de teclado
			const Uint8 * keyStatesActuales = SDL_GetKeyboardState(NULL);

			//Pausa
			if (keyStatesActuales[SDL_SCANCODE_ESCAPE])
				pJuego->setEstadoEnum (MPausa);
			
			//Personaje
			psj->onInput();
			if (!pasoNivel && !nivelCambiado)
				compruebaColisionPersonaje();



		}
		

	}


//Destruir objetos
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

		if (getLLavesCogidas(0))
			setLlaveCogida(1);//Pone a true la llave a eliminar en el array de booleanos de las llaves de juego
		else
			setLlaveCogida(0);//Pone a true la llave a eliminar en el array de booleanos de las llaves de juego
	}
void Mundo::destruyeArma(){
		list<Armas*>::iterator it = armas.begin();
		while (it != armas.end() && !checkCollision((*it)->getRect(),psj->getRect()))//Recorre todas las armas hasta encontrar el arma que tiene que destruir
		{
			it++;
		}
		psj->cogeArma((*it));
		it = armas.erase(it);
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

//Colisiones
EntidadJuego * Mundo::compruebaColisionObjetos(){
		size_t i = 0;
		SDL_Rect rect, rect3;

		rect.x = psj->getRect().x;
		rect.y = psj->getRect().y;

		//Rect3 = rect de colision
		rect3.h = 10;
		rect3.w = 10;
		rect3.x = rect.x + 10;
		rect3.y = rect.y + 40;


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
		list<Armas*>::const_iterator itArmas = armas.cbegin();

		while (!armas.empty() && itArmas != armas.cend() && !checkCollision(psj->getRect(), (*itArmas)->getRect()))
		{
			itArmas++;
		}
		if (it == llaves.cend() && itArmas == armas.cend())
			return nullptr;
		else if (itArmas != armas.cend())
			return (*itArmas);
		else
			return (*it);
	}
void Mundo::compruebaColisionPersonaje(){
	SDL_Rect rectPersonaje = psj->getRect(), rectPies;

	int x, y;


	//Reducimos el ancho y alto del rectangulo de colision
	rectPies.h = 10;
	rectPies.w = 10;

	x = rectPersonaje.x - psj->DamePosAntX();
	y = rectPersonaje.y - psj->DamePosAntY();

	//Movemos el rectangulo de colision a los pies
	rectPies.x = rectPersonaje.x + 10;
	rectPies.y = rectPersonaje.y + 40;

	Direccion dir;
	dir.x = x;
	dir.y = y;
	psj->setDir(dir);

	int tipo;
	mapa->touchesDoor(rectPies, tipo);

	
	/*if (mapa->touchesDoor(rectPies, tipo))
	{

		EstadoJuego * aux = new PasoDeNivel(pJuego);
		pJuego->goToState(aux);
	}*/

	//comprueba la X
	if (mapa->touchesWall(rectPies)){
		rectPersonaje.x -= x;
	}
	// comprueba la Y
	if (mapa->touchesWall(rectPies)){
		rectPersonaje.y -= y;
	}

	//Felpudos
	if (tipo != 150 && tipo != 155 && tipo != 154 && tipo != 140 && tipo != 158 && tipo != 165 && tipo != 159 && tipo != 153 && tipo != 152 && tipo != 151 && tipo != 114
		&& tipo != 345 && tipo != 350 && tipo != 349 && tipo != 335 && tipo != 353 && tipo != 360 && tipo != 354 && tipo != 348 && tipo != 347 && tipo != 346 && tipo != 309)
		psj->setPosChocando(rectPersonaje.x, rectPersonaje.y);

}
void Mundo::colBalaEnemigo(){

		list<Enemigo*>::iterator itEnemigo = enemigos.begin();

		//Recorremos los enemigos
		while (!enemigos.empty() && itEnemigo != enemigos.cend())
		{
			list<EntidadJuego*>::iterator it = balasPsj.begin();
			if (checkCollision(camera, (*itEnemigo)->getRect())){
				//Recorremos las balas
				while (!balasPsj.empty() && it != balasPsj.cend())
				{
					//Detectamos la colision de la bala con el enemigo
					if (checkCollision((*it)->getRect(), (*itEnemigo)->getRect()))
					{
						(*itEnemigo)->restaVida();
						destruyeBala(balasPsj, it);

						//Caso en el que el enemigo muere
						if ((*itEnemigo)->getVida() <= 0)
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
			else
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
			}
			else
				itBalasEnems++;
		}
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

//Cinematica
/*void Mundo::cinematicaInicial(){

		//comienza la cinematica, el jugador se encuentra en la cama y se deja de dibujar
		if (contador == 400)
			dibuja = false;

		//se vuelve a dibujar, y aparece el jugador en el mundo oscuro
		if (!dibuja && contador == 500){
			setCamera(800 * 1, indiceMapa % 6 * 640);
			psj->setRect({ 1120, 830, psj->getRect().w, psj->getRect().h }); //ESTO SE HARIA CON SETRECT DEL PERSONAJE
			dibuja = true;
		}

		//se deja de dibujar y se cambia al mundo real
		if (dibuja && contador == 600)
		{
			dibuja = false;
			setCamera(0, indiceMapa % 6 * 640);
			psj->setRect({ 320, 830, psj->getRect().w, psj->getRect().h });
			//camera.x = 320; camera.y = 830;
		}

		//se vuelve a dibujar, el jugador esta en la cama en el mundo real
		if (!dibuja && contador == 700)
		{
			dibuja = true;
		}

		if (dibuja && contador == 800)
		{
			dibuja = false;
		}

		if (moverP && veces < 100)
			veces++;
		if (moverP && veces == 100)
		{
			psj->mover(0, 1);
		}
		//lala 142833
		if (psj->getRect().y >= 860)
		{
			veces++;
		}
		if (moverP && veces >= 1)
			psj->mover(1, 0);


		if (!dibuja && contador == 900){
			psj->setRect({ 360, 900, psj->getRect().w, psj->getRect().h });
			dibuja = true;
			moverI = true;
		}

		if (moverI && contador >= 1000){
			objetos[1]->setVisible(true);
			objetos[1]->move(0, 1);
			moverP = true;
		}

		if (objetos[1]->getRect().y >= 950){
			moverI = false;
			cinematica = false;
			primeCinematica = false;
			psj->SetCinematica(cinematica);

		}

		if (psj->getRect().x >= 450)
		{
			moverP = false;

		}


	}*/