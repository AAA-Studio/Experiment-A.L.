#include "Combinaciones.h"
#include "Boton.h"
#include <iostream>
using namespace std;


static void cero(Juego* ju){ ju->setNumero(0); }
static void uno(Juego* ju){ ju->setNumero(1); }
static void dos(Juego* ju){ ju->setNumero(2); }
static void tres(Juego* ju){ ju->setNumero(3); }
static void cuatro(Juego* ju){ ju->setNumero(4); }
static void cinco(Juego* ju){ ju->setNumero(5); }
static void seis(Juego* ju){ ju->setNumero(6); }
static void siete(Juego* ju){ ju->setNumero(7); }
static void ocho(Juego* ju){ ju->setNumero(8); }
static void nueve(Juego* ju){ ju->setNumero(9); }
static void salir(Juego* ju){ ju->popState(); }
static void enter(Juego* ju){}

Combinaciones::Combinaciones(Juego* juego, string combinacion, int puerta) : Menu(juego)
{
	acierto = false;
	this->combinacion = combinacion;
	this->puerta = puerta;
	intentos = 0;
	combTecleada = "";
	initObjetos();
	boton = 1;
}

void Combinaciones::update(){
	
	Menu::update();

	if (combinacion == combTecleada)
		acierto = true;

	if (intentos == 4)
	{
		combTecleada = "";
		intentos = 0;
	}

}
void Combinaciones::initObjetos(){
	objetos.emplace_back(new Boton(pJuego, 370, 480, 60, 75, JuegoSDL::TCero, JuegoSDL::ENull, cero));
	objetos.emplace_back(new Boton(pJuego, 280, 190, 60, 75, JuegoSDL::TUno, JuegoSDL::ENull, uno));
	objetos.emplace_back(new Boton(pJuego, 370, 190, 60, 75, JuegoSDL::TDos, JuegoSDL::ENull, dos));
	objetos.emplace_back(new Boton(pJuego, 460, 190, 60, 75, JuegoSDL::TTres, JuegoSDL::ENull, tres));
	objetos.emplace_back(new Boton(pJuego, 280, 290, 60, 75, JuegoSDL::TCuatro, JuegoSDL::ENull, cuatro));
	objetos.emplace_back(new Boton(pJuego, 370, 290, 60, 75, JuegoSDL::TCinco, JuegoSDL::ENull, cinco));
	objetos.emplace_back(new Boton(pJuego, 460, 290, 60, 75, JuegoSDL::TSeis, JuegoSDL::ENull, seis));
	objetos.emplace_back(new Boton(pJuego, 280, 390, 60, 75, JuegoSDL::TSiete, JuegoSDL::ENull, siete));
	objetos.emplace_back(new Boton(pJuego, 370, 390, 60, 75, JuegoSDL::TOcho, JuegoSDL::ENull, ocho));
	objetos.emplace_back(new Boton(pJuego, 460, 390, 60, 75, JuegoSDL::TNueve, JuegoSDL::ENull, nueve));
	objetos.emplace_back(new Boton(pJuego, 280, 480, 60, 75, JuegoSDL::TVolver, JuegoSDL::ENull, salir));
	objetos.emplace_back(new Boton(pJuego, 460, 480, 60, 75, JuegoSDL::TCero, JuegoSDL::ENull, enter));
	objetos.emplace_back(new Boton(pJuego, 200, 100, 400, 500, JuegoSDL::TKeypad, JuegoSDL::ENull, enter));
	}

void Combinaciones::draw() const{
	//for (int i = objetos.size() - 1; i >= 0; i--)
		//objetos[i]->draw(objetos[i]->getRect().x, objetos[i]->getRect().y);
	//int i = 7;
	
	objetos[objetos.size() - 1]->draw(objetos[objetos.size() - 1]->getRect().x, objetos[objetos.size() - 1]->getRect().y);
	objetos[boton]->draw(objetos[boton]->getRect().x, objetos[boton]->getRect().y);

}

void Combinaciones::onInput(SDL_Event &e){

	if (e.type == SDL_KEYUP){ //si se pulsa una tecla comprueba que es p
		if (e.key.keysym.sym == SDLK_RETURN)
		{
			if (boton == 11)
				pulsaEnter();
			else if (boton == 10)
				pulsaSalir();
			else
			{
				combTecleada += to_string(boton);
				cout << " intentos: " + intentos;
				cout << " combinacion: " + combTecleada;
				intentos++;
			}
		}
		else if (e.key.keysym.sym == SDLK_RIGHT && boton != 3 && boton != 6 && boton != 9 && boton != 11)
		{
			if (boton == 0)
				boton = 11;
			else if (boton == 10)
				boton = 0;
			else 
				boton += 1;
		}
		else if (e.key.keysym.sym == SDLK_LEFT && boton != 1 && boton != 4 && boton != 7 && boton != 10)
		{
			if (boton == 0)
				boton = 10;
			else if (boton == 11)
				boton = 0;
			else
				boton -= 1;
		}
		else if (e.key.keysym.sym == SDLK_UP && boton != 1 && boton != 2 && boton != 3)
		{
			if (boton == 0)
				boton = 8;
			else if (boton == 11)
				boton = 9;
			else
				boton -= 3;
		}
		else if (e.key.keysym.sym == SDLK_DOWN && boton != 10 && boton != 11 && boton != 0)
		{
			if (boton == 8)
				boton = 0;
			else if (boton == 9)
				boton = 11;
			else
				boton += 3;
		}
		
	}
	/*if (e.type == SDL_MOUSEBUTTONUP)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			for (int j = 0; j < objetos.size(); j++)
			{
				objetos[j]->onInput();
			}
			int i = 0;
			bool pulsado = false;
			
			while (i < objetos.size() && !pulsado)
			{
				//objetos[i]->onInput();
				if (i == 10)
					pulsado == true;
				else if (pJuego->getNumero() == i)
				{
					combTecleada += to_string(pJuego->getNumero());
					intentos++;
					pulsado = true;
					cout << " intentos: " + intentos;
					cout << " combinacion: " + combTecleada;
					pJuego->setNumero(20);
				}
				
				i++;
			}
			pulsado = false;
			i = 0;
		}
	}*/

}

void Combinaciones::pulsaEnter()
{
	if (acierto)
	{
		pJuego->setPuerta(puerta, acierto);
		pJuego->popState();
	}
}

void Combinaciones::pulsaSalir()
{
	pJuego->popState();
}