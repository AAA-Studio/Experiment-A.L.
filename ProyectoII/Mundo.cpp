#include "Mundo.h"
#include <typeinfo>
#include "Personaje.h"
#include <iostream>
#include <SDL.h>
#include "Bala.h"
#include "Boton.h"
#include <fstream>
#include "Enemigo1.h"
#include "Enemigo2.h"
#include "Enemigo3.h"
#include "Enemigo4.h"
#include "Enemigo5.h"
#include "BossFinal.h"


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
	contCinematFinal = 0;
	muestraTexto = false;
	decremNegro = false;

	pasoNivel = false;
	psjMovidos = batallaBoss = bossMuerto =false;
	//objetos[1]->setVisible(false);
	pJuego->getResources()->getMusica(JuegoSDL::Musica_t::MReal)->play();

	psj->empiezaPerderVida();

	for (int i = 0; i < TAMAÑO_LLAVES; i++) //Se inicializan las llaves
		llavesCogidas[i] = false;

	alfo = 0;
	pJuego->getResources()->getTextura(JuegoSDL::TNegro)->setAlpha(alfo);
	nivelCambiado = false;
	colObjeto =  false;

	for (int i = 0; i < 1; i++)
		pJuego->setPuerta(i, false);

	//Fuente
	font_ = pJuego->getResources()->getFuente(JuegoSDL::Fuentes_t::FNormal);
	textBalas.loadFromText(pJuego->getRender(), "Balas : " + to_string(psj->getBalas()), { 255, 255, 255, 1 }, *font_);
	textCogerObj.loadFromText(pJuego->getRender(), "Pulsa 'E' para interactuar", { 255, 255, 255, 1 }, *font_);
	textPlanta.loadFromText(pJuego->getRender(), "PLANTA 5", { 255, 255, 255, 1 }, *font_);
	textConversDocT.loadFromText(pJuego->getRender(), "Parece que finalmente lo has comprendido todo.. ¿o no?", { 255, 255, 255, 1 }, *font_);
	rectEspejo = { 0, 0, pJuego->getResources()->getTextura(JuegoSDL::TAnimacionEspejo)->getW() / 4, pJuego->getResources()->getTextura(JuegoSDL::TAnimacionEspejo)->getH() };
	rectColDoctorT = { doctorT->getRect().x + 10, doctorT->getRect().y + 40, doctorT->getRect().w - 10, doctorT->getRect().h - 40 };
	textArriba = false;

	contadorEspejo = 0;
	cinematicaEncuentroBoss = false;
	periodicoPuesto = false;
}

Mundo::~Mundo()
{
	freeObjetos();

	pJuego->getResources()->getMusica(JuegoSDL::MReal)->closeAndLoad();
	pJuego->getResources()->getMusica(JuegoSDL::MOscuro)->closeAndLoad();


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
	int y, x, w, h, lvl, tipo, ancho, alto,salud;
	char xar;
	int max;
	alto = 640;
	while (obj.peek() != EOF){


		if (i == 1)
			obj >> nombre;


		int cadencia,balas;
		if (nombre == "NIVEL"){

			obj >> lvl;
			obj >> nombre;

			if (lvl < 24)
				ancho = 0;
			else
				ancho = 800;


			while (obj.peek() != EOF && nombre != "NIVEL"){
				if (nombre == "LLAVE"){
					obj >> x >> y >> w >> h;
					llaves.push_back(new Entidad(pJuego, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TLlave, JuegoSDL::ENull, OLlave));
				}
				else if (nombre == "INFORME"){
					obj >> x >> y >> w >> h >> tipo;
					if (tipo == 1)
						objetos.push_back(new Entidad(pJuego, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TInforme1, JuegoSDL::ENull, OInforme1));//Informe
					else if (tipo == 2)
						objetos.push_back(new Entidad(pJuego, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TInforme2, JuegoSDL::ENull, OInforme2));//Informe
					else if (tipo == 3)
						objetos.push_back(new Entidad(pJuego, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TInforme3, JuegoSDL::ENull, OInforme3));//Informe
					else if (tipo == 4)
						objetos.push_back(new Entidad(pJuego, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TInforme4, JuegoSDL::ENull, OInforme4));//Informe
					else if (tipo == 5)
						objetos.push_back(new Entidad(pJuego, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TInforme5, JuegoSDL::ENull, OInforme5));//Informe
					else if (tipo == 6)
						objetos.push_back(new Entidad(pJuego, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TInforme6, JuegoSDL::ENull, OInforme6));//Informe
					else if (tipo == 7)
						objetos.push_back(new Entidad(pJuego, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TInforme7, JuegoSDL::ENull, OInforme7));//Informe
				}
				else if (nombre == "PANEL"){

					obj >> x >> y >> w >> h;
					objetos.push_back(new Entidad(pJuego, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TTeclado, JuegoSDL::ENull, OTeclado));
				}
				else if (nombre == "ARMA"){

					obj >> x >> y >> w >> h >> balas >> cadencia;
					armas.push_back(new Armas(pJuego, x + ancho, y + alto*(lvl % 24), w, h, balas, cadencia, JuegoSDL::TPistola, JuegoSDL::ENull, OPistola));
				}
				//IMPORTANTE: Enemigo2 usa TEnemigo2, Enemigo4 usa TEnemigo4.
				else if (nombre == "ENEMIGO"){

					obj >> x >> y >> w >> h >> tipo;

					if (tipo == 1)
						enemigos.push_back(new Enemigo1(this, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TLeon, JuegoSDL::ENull));
					else if (tipo == 2){ //ESTO ES TU TRABAJO BLANCA NO TOCAR
						obj >> xar >> max;
						enemigos.push_back(new Enemigo2(this, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TEnemigo2, JuegoSDL::ENull, xar, max));
					}
					else if (tipo == 3)
						enemigos.push_back(new Enemigo3(this, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TEnemigo3, JuegoSDL::ENull));
					else if (tipo == 4)
						enemigos.push_back(new Enemigo4(this, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TEnemigo4, JuegoSDL::ENull));
					else if (tipo == 5)
						enemigos.push_back(new Enemigo5(this, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TEnemigo5, JuegoSDL::ENull));
				}
				else if (nombre == "SALUD"){

					obj >> x >> y >> w >> h >> salud >> tipo;
					if (tipo == 1)
						pildoras.push_back(new Pildoras(pJuego, x + ancho, y + alto*(lvl % 24), w, h, salud, JuegoSDL::TPildora, JuegoSDL::ENull, OPildoras));
					if (tipo == 2)
						pildoras.push_back(new Pildoras(pJuego, x + ancho, y + alto*(lvl % 24), w, h, salud, JuegoSDL::TBotePildora, JuegoSDL::ENull, OPildoras));
				}
				else if (nombre == "INTERRUPTOR"){

					obj >> x >> y >> w >> h >> tipo;
					if (tipo == 1)
						interruptores.push_back(new Interruptor(pJuego, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TInterruptor, JuegoSDL::ENull, OInterruptor1));
					else if (tipo == 2)
						interruptores.push_back(new Interruptor(pJuego, x + ancho, y + alto*(lvl % 24), w, h, JuegoSDL::TInterruptor, JuegoSDL::ENull, OInterruptor2));
				}
				obj >> nombre;

			}
		}
		i++;
	}
	obj.close();
	
	//enemigo = new Enemigo2(this, 400, 900, 25, 25, JuegoSDL::TEnemigo2, JuegoSDL::ENull, 'x', 100);
	//enemigos.push_back(new Enemigo3(this, 400, 900, 25, 25, JuegoSDL::TEnemigo3, JuegoSDL::ENull));

}
void Mundo::initObjetos()
{	
	int x = 360;
	int y = 900;

	//Esta posicion es para mover al personaje a la sala final del mundo real para hacer la cinematica con el doctor T
	//psj = new Personaje(this, 400, 3840 * 2 + 3200 * 2 + 800, JuegoSDL::TJugador, JuegoSDL::ENull);

	//psj = new Personaje(this, x, y, JuegoSDL::TJugador, JuegoSDL::ENull);
	doctorT = new DoctorT(pJuego, 400, 3840 * 2 + 3200 * 2 + 900, 30, 50, JuegoSDL::TDoctorT, JuegoSDL::ENull);
	//x = mapa->getXSpawn();
	//y = mapa->getYSpawn();
	psj = new Personaje(this, x, y, JuegoSDL::TJugador, JuegoSDL::ENull);
	
}

void Mundo::freeObjetos(){
		delete psj;
		psj = nullptr;


		list<EntidadJuego*>::const_iterator itObj = objetos.cbegin();
		while (!objetos.empty() && itObj != objetos.end())
		{
			delete(*itObj);
			itObj= objetos.erase(itObj);
		
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

		list<Armas*>::iterator itArmas = armas.begin();
		while (!armas.empty() && itArmas != armas.end())
		{
			delete(*itArmas);
			itArmas = armas.erase(itArmas);
		}

		list<Pildoras*>::iterator itpil = pildoras.begin();
		while (!pildoras.empty() && itpil != pildoras.end())
		{
			delete(*itpil);
			itpil = pildoras.erase(itpil);
		}

		list<Interruptor*>::iterator itInterr = interruptores.begin();
		while (!interruptores.empty() && itInterr != interruptores.end())
		{
			delete(*itInterr);
			itInterr = interruptores.erase(itInterr);
		}

	}

void Mundo::draw()const{

	SDL_Rect winRectEspejo = { 0, 0, 32, 32 };


	//DIBUJAR MAPA
	mapa->draw();

	pJuego->getResources()->getTextura(JuegoSDL::TAnimacionEspejo)->draw(pJuego->getRender(), winRectEspejo, 382 - camera.x, 3392 - camera.y, &rectEspejo);
	pJuego->getResources()->getTextura(JuegoSDL::TAnimacionEspejo)->draw(pJuego->getRender(), winRectEspejo, 480 - camera.x, 10336 - camera.y, &rectEspejo);

	//Dibujar objetos del juego
	//Armas
	for (auto arma : armas)
		arma->draw(arma->getRect().x - camera.x, arma->getRect().y - camera.y);

	for (auto pildora : pildoras)
		pildora->draw(pildora->getRect().x - camera.x, pildora->getRect().y - camera.y);

	for (auto objeto: objetos)
		objeto->draw(objeto->getRect().x - camera.x, objeto->getRect().y - camera.y);

	for (auto inter : interruptores)
		inter->draw(inter->getRect().x - camera.x, inter->getRect().y - camera.y);

	for (auto llave : llaves)
		llave->draw(llave->getRect().x - camera.x, llave->getRect().y - camera.y);

	for (auto enemigo : enemigos)
		enemigo->draw(enemigo->getRect().x - camera.x, enemigo->getRect().y - camera.y);


	psj->draw(psj->getRect().x - camera.x, psj->getRect().y - camera.y);
	//Si el doctorT existe se dibuja
	if (doctorT != nullptr)
		doctorT->draw(doctorT->getRect().x - camera.x, doctorT->getRect().y - camera.y);
	
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
	//pJuego->getResources()->getTextura(JuegoSDL::TControles)->draw(pJuego->getRender(), a, 0, 0, nullptr);
	//Dibujo las balas restantes si no hay arma este sera 0
	a.h = 30;
	a.w = 90;


	//Dibujar fondo negro
	a.h = 640;
	a.w = 800;


	
	pJuego->getResources()->getTextura(JuegoSDL::TNegro)->draw(pJuego->getRender(), a, 0, 0, nullptr);
	

	
	if (colObjeto)
	{
		textCogerObj.renderFont(pJuego->getRender(), psj->getRect().x - camera.x - 20, psj->getRect().y - camera.y + 50);
	}
	if (textArriba){
		a.h = 80;
		a.w = 240;
		textPlanta.draw(pJuego->getRender(), a, 280, 250, nullptr);
	}

	//Caso en el que has cogido la pistola
	else if (psj->getBalas() > 0){
		textBalas.renderFont(pJuego->getRender(), 400, 600);
	}
	if (muestraTexto){
		textConversDocT.renderFont(pJuego->getRender(), 150, 500);

		
	}

	if (pasoNivel || nivelCambiado || cinematicaEncuentroBoss || bossMuerto)
		pJuego->getResources()->getTextura(JuegoSDL::TNegro)->setAlpha(alfo);

	if (periodicoPuesto){
		pJuego->getResources()->getTextura(JuegoSDL::TPeriodico)->draw(pJuego->getRender(), { 0, 0, 850, 640 }, -30, 0,nullptr);
		textConversDocT.renderFont(pJuego->getRender(), 40, pJuego->getWindowHeight() - 30);
	}
	
}

void Mundo::update(){
		psj->update();//Update de personaje
		balaDestruida = false;
		colObjeto = false;

		if (contadorEspejo == 5)
		{
			rectEspejo.x = (rectEspejo.x + pJuego->getResources()->getTextura(JuegoSDL::TAnimacionEspejo)->getW() / 4) % pJuego->getResources()->getTextura(JuegoSDL::TAnimacionEspejo)->getW();
			contadorEspejo = 0;
		}
		else
			contadorEspejo++;
		//NO SE TOCA
		textBalas.loadFromText(pJuego->getRender(), "Balas : " + to_string(psj->getBalas()), { 255, 255, 255, 1 }, *font_);
		////////////////
		

		//Caso GameOver
		if (psj->getVida() <= 0){
			pJuego->setEstadoEnum(EGameOver);
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
			balaDestruida = false;
			if (checkCollision(camera, (*itBalasEnem)->getRect()))
			{
				(*itBalasEnem)->update();
				if (!balaDestruida && mapa->touchesWall((*itBalasEnem)->getRect())){
					delete (*itBalasEnem);
					itBalasEnem = balasEnems.erase(itBalasEnem);
					balaDestruida = true;
				}
				else
					itBalasEnem++;
			}
			else
				itBalasEnem++;
		}
		//Enemigos
		for (auto enemigo : enemigos){
			if (checkCollision(camera, enemigo->getRect())){
				enemigo->update();
				compruebaColisionEnemigo(enemigo);
				//Si el personaje choca con el enemigo, resto vida
				if (checkCollision(psj->getRect(), enemigo->getRect()))
					psj->restaVida(0.005);
					
			}


			//COLISIONES ENEMIGO 
			
		}

		//Colision del personaje con el malo final
		if (doctorT!=nullptr && checkCollision(camera, doctorT->getRect())){
			if (checkCollision(doctorT->getRect(), psj->getRect())){
				//Se muestra el texto con el malo final
				//El personaje no se mueve
				setNivel(24);
				setCurapsj();
				setMundo(Mundo_t::MOscuro);
				psj->setRect({ psj->getRect().x, psj->getRect().y - 1, psj->getRect().w, psj->getRect().h });
				cinematicaEncuentroBoss = true;
				muestraTexto = true;

			}

			}
			if (cinematicaEncuentroBoss || batallaBoss)
				contCinematFinal++;


			//Update de objetos
			list<EntidadJuego*>::iterator obj = objetos.begin();

			while (!colObjeto && !objetos.empty() && obj != objetos.end()){
				if (checkCollision(camera, (*obj)->getRect())){
					if (checkCollision(psj->getRect(), (*obj)->getRect()))
						colObjeto = true;
				
					else				
						colObjeto = false;
				
				}
				(*obj)->update();

				obj++;
			}
			list<EntidadJuego*>::iterator itLlave = llaves.begin();

			//Update de las llaves
			while (!colObjeto && !llaves.empty() && itLlave != llaves.end()){
				if (checkCollision(camera, (*itLlave)->getRect()))
				{
					if (checkCollision(psj->getRect(), (*itLlave)->getRect()))
					{
						colObjeto = true;

					}
					else
					{
						colObjeto = false;
					}


				}

				(*itLlave)->update();
				itLlave++;
			}


			list<Armas*>::iterator itArma = armas.begin();

			//Update de las armas
			while (!colObjeto && !armas.empty() && itArma != armas.end()){
				if (checkCollision(camera, (*itArma)->getRect()))
				{
					if (checkCollision(psj->getRect(), (*itArma)->getRect()))
					{
						colObjeto = true;

					}
					else
					{
						colObjeto = false;
					}

				}

				(*itArma)->update();
				itArma++;
			}

			list<Pildoras*>::iterator itPil = pildoras.begin();

			//Update de las pildoras
			while (!colObjeto && !pildoras.empty() && itPil != pildoras.end()){
				if (checkCollision(camera, (*itPil)->getRect()))
				{
					if (checkCollision(psj->getRect(), (*itPil)->getRect()))
					{
						colObjeto = true;

					}
					else
					{
						colObjeto = false;
					}

				}

				(*itPil)->update();
				itPil++;
			}

			list<Interruptor*>::iterator itInter = interruptores.begin();

			//Update de las interruptor
			while (!colObjeto && !interruptores.empty() && itInter != interruptores.end()){
				if (checkCollision(camera, (*itInter)->getRect()))
				{
					if (checkCollision(psj->getRect(), (*itInter)->getRect()))
					{
						colObjeto = true;

					}
					else
					{
						colObjeto = false;
					}

				}

				(*itInter)->update();
				itInter++;
			}
			//COLISIONES
			colBalaEnemigo();
			colBalaPersonaje();
			//Transicion nivel
			if (pasoNivel){
				alfo += 5;

				if (alfo > 255){
					pasoNivel = false;
					nivelCambiado = true;
					mapa->buscaSpawn();
				}

			}
			if (nivelCambiado){
				alfo -= 10;
				if (alfo == 0)//Se pide la hora y se compara con la última 
				{
					alfo = 0;
					nivelCambiado = false;
					textArriba = false;
				}

			}

			//-------------------------CINEMATICA BOSS----------------------------------
			//Caso de transicion a negro en la cinematica final
			if (contCinematFinal == 200){
				muestraTexto = false;
			}
			else if (contCinematFinal > 200 && contCinematFinal < 350){
				if (!decremNegro)//Caso en el que incremento el alfa
					alfo += 5;

				if (alfo == 255){
					//Mover la camara, jugador, y doctor al mundo oscuro
					camera.x = 800;
					psj->setRect({ psj->getRect().x + 800, psj->getRect().y, psj->getRect().w, psj->getRect().h });
					doctorT->setRect({ doctorT->getRect().x + 800, doctorT->getRect().y + 200, doctorT->getRect().w, doctorT->getRect().h });
					doctorT->setRectAnim();
					psjMovidos = true;
				}
				 if (psjMovidos){//Cuando he movido la camara y lo demas, decremento el alfa
					alfo -= 5;
					decremNegro = true;
					
				}
				if (alfo <= 0)//Se termina la transicion de negro
				{
					psjMovidos = false;
					alfo = 0;

				}

			}
			else if (contCinematFinal == 350){
				textConversDocT.loadFromText(pJuego->getRender(), "                                 ¡ENFRENTATE A TUS MIEDOS!", { 255, 255, 255, 1 }, *font_);
				muestraTexto = true;
			}
			else if (contCinematFinal == 450){
				muestraTexto = false;
				//Creo el boss
				cinematicaEncuentroBoss = false;
				batallaBoss = true;
				enemigos.push_back(new BossFinal(this, doctorT->getRect().x, doctorT->getRect().y, doctorT->getRect().w, doctorT->getRect().h, JuegoSDL::TBoss, JuegoSDL::ENull));
				//Destruyo al doctor T
				delete(doctorT);
				doctorT = nullptr;
			

			}

			//-------------------------CINEMATICA BOSS----------------------------------

			//-------------------------CINEMATICA FINAL----------------------------------
			if (bossMuerto && contCinematFinal >= 700){
				muestraTexto = false;
				//Transicion a negro
				if (!decremNegro)//Caso en el que incremento el alfa
					alfo += 5;

				if (alfo == 255){
					//Mostrar el periodico
								
					periodicoPuesto = true;
				}
				if (periodicoPuesto){//Cuando he movido la camara y lo demas, decremento el alfa
					textConversDocT.loadFromText(pJuego->getRender(), "Pulsa ESPACIO para salir", { 0, 0, 0, 1 }, *font_);
	
					alfo -= 5;
					decremNegro = true;

				}
				if (alfo <= 0)//Se termina la transicion de negro
				{
					psjMovidos = false;
					alfo = 0;

				}
			}
			//-------------------------CINEMATICA FINAL----------------------------------

		}
		
	
void Mundo::onInput(SDL_Event &e)
{
	const Uint8 * keyStatesActuales = SDL_GetKeyboardState(NULL);
		if (!nivelCambiado && !pasoNivel && !cinematicaEncuentroBoss && !bossMuerto) // NO PLS
		{
			//Declaramos el array con los estados de teclado
			

			//Pausa
			if (keyStatesActuales[SDL_SCANCODE_ESCAPE])
			{
				pJuego->setEstadoEnum(MPausa);
				pJuego->setBorraEstado(true);
			}
			
			//Personaje
			psj->onInput();
			compruebaColisionPersonaje();

		}
		//Caso para salir de la escena del periodico al menu de Inicio
		else if (periodicoPuesto){
			if (keyStatesActuales[SDL_SCANCODE_SPACE]){
				pJuego->setEstadoEnum(MInicio);
				pJuego->setBorraEstado(true);
			}
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

		pJuego->getResources()->getEfecto(7)->play(0);


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
		pJuego->getResources()->getEfecto(7)->play(0);

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
void Mundo::pildoraCogida(){
	list<Pildoras*>::iterator it = pildoras.begin();
	while (it != pildoras.end() && !checkCollision((*it)->getRect(), psj->getRect()))//Recorre todas las llaves hasta encontrar la llave que tiene que destruir
	{
		it++;
	}
	psj->sumaVida((*it)->getSalud());
	delete (*it);
	it = pildoras.erase(it);
}
void Mundo::setPulsado(){
	mapa->setPulsado(true);
}
void Mundo::setPulsado2(){
	mapa->setPulsado2(true);
}

void Mundo::destruyeInterruptor(){
	list<Interruptor*>::const_iterator itInterrup = interruptores.cbegin();

	while (!interruptores.empty() && itInterrup != interruptores.cend() && !checkCollision(psj->getRect(), (*itInterrup)->getRect()))
	{
		itInterrup++;
	}
	delete (*itInterrup);
	itInterrup = interruptores.erase(itInterrup);
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


		list<EntidadJuego*>::const_iterator itObj = objetos.cbegin();

		while (!objetos.empty() && itObj != objetos.cend() && !checkCollision(psj->getRect(), (*itObj)->getRect()))
			itObj++;

		//Si lo he encontrado en los informes
		if (itObj != objetos.cend())
			return (*itObj);

		//Si no, sigo buscando en la lista de llaves
		list<EntidadJuego*>::const_iterator it = llaves.cbegin();

		while (!llaves.empty() && it != llaves.cend() && !checkCollision(psj->getRect(), (*it)->getRect()))
			it++;

		if (it != llaves.cend())
			return (*it);
	
		list<Pildoras*>::const_iterator itPildora = pildoras.cbegin();

		while (!pildoras.empty() && itPildora != pildoras.cend() && !checkCollision(psj->getRect(), (*itPildora)->getRect()))
		{
			itPildora++;
		}
		if (itPildora != pildoras.cend())
			return(*itPildora);

		list<Armas*>::const_iterator itArmas = armas.cbegin();

		while (!armas.empty() && itArmas != armas.cend() && !checkCollision(psj->getRect(), (*itArmas)->getRect()))
			itArmas++;
		
		if (itArmas != armas.cend())
			return (*itArmas);

		list<Interruptor*>::const_iterator itInterrup = interruptores.cbegin();

		while (!interruptores.empty() && itInterrup != interruptores.cend() && !checkCollision(psj->getRect(), (*itInterrup)->getRect()))
		{
			itInterrup++;
		}
		if (itInterrup != interruptores.cend())
			return (*itInterrup);

		return nullptr;
	}

void Mundo::compruebaColisionEnemigo(Enemigo* enemigo)
{
	SDL_Rect rectEnemigo = enemigo->getRect();

	int x, y;


	//Reducimos el ancho y alto del rectangulo de colision

	x = rectEnemigo.x - enemigo->DamePosAntX();
	y = rectEnemigo.y - enemigo->DamePosAntY();

	//Movemos el rectangulo de colision a los pies

	int tipo;
	mapa->touchesDoor(rectEnemigo, tipo);

	// comprueba la Y
	if (mapa->touchesWall(rectEnemigo)){
		
		rectEnemigo.y -= y;

		enemigo->colision(true);
	}
	else 
		enemigo->colision(false);
	//comprueba la X
	if (mapa->touchesWall(rectEnemigo)){
		rectEnemigo.x -= x;
		enemigo->colision(true);
	}
	else 
		enemigo->colision(false);


	//Felpudos
	if (tipo != 0
		&& tipo != 1
		&& tipo != 2
		&& tipo != 3
		&& tipo != 4
		&& tipo != 5
		&& tipo != 6
		&& tipo != 7
		&& tipo != 16
		&& tipo != 17
		&& tipo != 18
		&& tipo != 19
		&& tipo != 20
		&& tipo != 21
		&& tipo != 22
		&& tipo != 27
		&& tipo != 28
		&& tipo != 29
		&& tipo != 30
		&& tipo != 31
		&& tipo != 32
		&& tipo != 33
		&& tipo != 42
		&& tipo != 43
		&& tipo != 44
		&& tipo != 54
		&& tipo != 55
		&& tipo != 57
		&& tipo != 58
		&& tipo != 59
		&& tipo != 114
		&& tipo != 140
		&& tipo != 150
		&& tipo != 151
		&& tipo != 152
		&& tipo != 153
		&& tipo != 154
		&& tipo != 155
		&& tipo != 157
		&& tipo != 158
		&& tipo != 159
		&& tipo != 165
		&& tipo != 169
		&& tipo != 174
		&& tipo != 180
		&& tipo != 181
		&& tipo != 182
		&& tipo != 183
		&& tipo != 184
		&& tipo != 185
		&& tipo != 186
		&& tipo != 187
		&& tipo != 188
		&& tipo != 189
		&& tipo != 190
		&& tipo != 191
		&& tipo != 281
		&& tipo != 282
		&& tipo != 338
		&& tipo != 339
		&& tipo != 340
		//------------------------------------------------------------------------------------//
		//                                      MUNDO OSCURO								  //
		//------------------------------------------------------------------------------------//

		&& tipo != 345
		&& tipo != 346
		&& tipo != 347
		&& tipo != 348
		&& tipo != 349
		&& tipo != 350
		&& tipo != 351
		&& tipo != 352
		&& tipo != 361
		&& tipo != 362
		&& tipo != 363
		&& tipo != 364
		&& tipo != 365
		&& tipo != 366
		&& tipo != 367
		&& tipo != 372
		&& tipo != 373
		&& tipo != 374
		&& tipo != 375
		&& tipo != 376
		&& tipo != 377
		&& tipo != 378
		&& tipo != 387
		&& tipo != 388
		&& tipo != 389
		&& tipo != 399
		&& tipo != 400
		&& tipo != 402
		&& tipo != 403
		&& tipo != 404
		&& tipo != 459
		&& tipo != 485
		&& tipo != 495
		&& tipo != 496
		&& tipo != 497
		&& tipo != 498
		&& tipo != 499
		&& tipo != 500
		&& tipo != 501
		&& tipo != 502
		&& tipo != 503
		&& tipo != 504
		&& tipo != 510
		&& tipo != 514
		&& tipo != 519
		&& tipo != 525
		&& tipo != 526
		&& tipo != 527
		&& tipo != 528
		&& tipo != 529
		&& tipo != 530
		&& tipo != 531
		&& tipo != 532
		&& tipo != 533
		&& tipo != 534
		&& tipo != 535
		&& tipo != 536
		&& tipo != 626
		&& tipo != 627
		&& tipo != 683
		&& tipo != 684
		&& tipo != 685)
		enemigo->setPosChocando(rectEnemigo.x, rectEnemigo.y);
		
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


	//comprueba la X
	//Si choca con la pared o con el doctor T, va hacia atras
	if (mapa->touchesWall(rectPies)){
	
		rectPersonaje.x -= x;
	}
	// comprueba la Y
	if (mapa->touchesWall(rectPies) ){
		rectPersonaje.y -= y;
	}

	//Felpudos
	if (tipo != 0
		&& tipo != 1
		&& tipo != 2
		&& tipo != 3
		&& tipo != 4
		&& tipo != 5
		&& tipo != 6
		&& tipo != 7
		&& tipo != 16
		&& tipo != 17
		&& tipo != 18
		&& tipo != 19
		&& tipo != 20
		&& tipo != 21
		&& tipo != 22
		&& tipo != 27
		&& tipo != 28
		&& tipo != 29
		&& tipo != 30
		&& tipo != 31
		&& tipo != 32
		&& tipo != 33
		&& tipo != 42
		&& tipo != 43
		&& tipo != 44
		&& tipo != 54
		&& tipo != 55
		&& tipo != 57
		&& tipo != 58
		&& tipo != 59
		&& tipo != 114
		&& tipo != 140
		&& tipo != 150
		&& tipo != 151
		&& tipo != 152
		&& tipo != 153
		&& tipo != 154
		&& tipo != 155
		&& tipo != 157
		&& tipo != 158
		&& tipo != 159
		&& tipo != 165
		&& tipo != 169
		&& tipo != 174
		&& tipo != 180
		&& tipo != 181
		&& tipo != 182
		&& tipo != 183
		&& tipo != 184
		&& tipo != 185
		&& tipo != 186
		&& tipo != 187
		&& tipo != 188
		&& tipo != 189
		&& tipo != 190
		&& tipo != 191
		&& tipo != 281
		&& tipo != 282
		&& tipo != 338
		&& tipo != 339
		&& tipo != 340
		//------------------------------------------------------------------------------------//
		//                                      MUNDO OSCURO								  //
		//------------------------------------------------------------------------------------//

		&& tipo != 345
		&& tipo != 346
		&& tipo != 347
		&& tipo != 348
		&& tipo != 349
		&& tipo != 350
		&& tipo != 351
		&& tipo != 352
		&& tipo != 361
		&& tipo != 362
		&& tipo != 363
		&& tipo != 364
		&& tipo != 365
		&& tipo != 366
		&& tipo != 367
		&& tipo != 372
		&& tipo != 373
		&& tipo != 374
		&& tipo != 375
		&& tipo != 376
		&& tipo != 377
		&& tipo != 378
		&& tipo != 387
		&& tipo != 388
		&& tipo != 389
		&& tipo != 399
		&& tipo != 400
		&& tipo != 402
		&& tipo != 403
		&& tipo != 404
		&& tipo != 459
		&& tipo != 485
		&& tipo != 495
		&& tipo != 496
		&& tipo != 497
		&& tipo != 498
		&& tipo != 499
		&& tipo != 500
		&& tipo != 501
		&& tipo != 502
		&& tipo != 503
		&& tipo != 504
		&& tipo != 510
		&& tipo != 514
		&& tipo != 519
		&& tipo != 525
		&& tipo != 526
		&& tipo != 527
		&& tipo != 528
		&& tipo != 529
		&& tipo != 530
		&& tipo != 531
		&& tipo != 532
		&& tipo != 533
		&& tipo != 534
		&& tipo != 535
		&& tipo != 536
		&& tipo != 626
		&& tipo != 627
		&& tipo != 683
		&& tipo != 684
		&& tipo != 685)
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
				if (!enemigos.empty() && !(itEnemigo == enemigos.end()))
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
				time = SDL_GetTicks();
				psj->restaVida(1);
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