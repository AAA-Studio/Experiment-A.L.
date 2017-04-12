#include "Combinaciones.h"
#include "Boton.h"
#include <iostream>
using namespace std;


static void cero(Juego* ju){ ju->numero = 0; }
static void uno(Juego* ju){ ju->numero = 1; }
static void dos(Juego* ju){ ju->numero = 2; }
static void tres(Juego* ju){ ju->numero = 3; }
static void cuatro(Juego* ju){ ju->numero = 4; }
static void cinco(Juego* ju){ ju->numero = 5; }
static void seis(Juego* ju){ ju->numero = 6; }
static void siete(Juego* ju){ ju->numero = 7; }
static void ocho(Juego* ju){ ju->numero = 8; }
static void nueve(Juego* ju){ ju->numero = 9; }

Combinaciones::Combinaciones(Juego* juego)
{
	this->juego = juego;
	acierto = false;
	combinacion = "1234";
	combTecleada = "";
	initObjetos();
}

void Combinaciones::update(){
	for (int i = 0; i < objetos.size(); i++)
		objetos[i]->update();

	if (combinacion == combTecleada)
		acierto = true;
	if (intentos == 4)
	{
		combTecleada = "";
		intentos = 0;
	}
}
void Combinaciones::initObjetos(){
	objetos.emplace_back(new Boton(juego, 500, 200, TUno, ENull, uno));
	objetos.emplace_back(new Boton(juego, 600, 200, TDos, ENull, dos));
	objetos.emplace_back(new Boton(juego, 700, 200, TTres, ENull, tres));
	objetos.emplace_back(new Boton(juego, 500, 300, TCuatro, ENull, cuatro));
	objetos.emplace_back(new Boton(juego, 600, 300, TCinco, ENull, cinco));
	objetos.emplace_back(new Boton(juego, 700, 300, TSeis, ENull, seis));
	objetos.emplace_back(new Boton(juego, 500, 400, TSiete, ENull, siete));
	objetos.emplace_back(new Boton(juego, 600, 400, TOcho, ENull, ocho));
	objetos.emplace_back(new Boton(juego, 700, 400, TNueve, ENull, nueve));
	objetos.emplace_back(new Boton(juego, 600, 500, TCero, ENull, cero));
	}

void Combinaciones::draw() const{
	/*SDL_Rect rect = { 500, 200, 225, 242 };
	juego->getTextura(TTeclado)->draw(juego->getRender(), rect);*/

	for (int i = objetos.size() - 1; i >= 0; i--)
		objetos[i]->draw();
	
}

void Combinaciones::onInput(SDL_Event &e){

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			int i = 0;
			while (i < objetos.size())
			{
				objetos[i]->onInput();
				if (juego->numero == i){
					combTecleada += to_string(juego->numero);
					intentos++;
					cout << combTecleada;
					if (acierto)
						cout << "acierto";
					else 
						cout << "fallo";
				}
				i++;
			}
		}
	}

}

Combinaciones::~Combinaciones()
{
}
