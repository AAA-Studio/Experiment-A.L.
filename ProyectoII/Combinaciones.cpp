#include "Combinaciones.h"
#include "Tecla.h"
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
	combinacion = "00";
	initObjetos();
}

void Combinaciones::update(){
	for (int i = 0; i < objetos.size(); i++)
		objetos[i]->update();

	if (combinacion == combTecleada)
		acierto = true;
}
void Combinaciones::initObjetos(){
	objetos.emplace_back(new Boton(juego, 200, 200, TExit, ENull, cero));

	//objetos.emplace_back(new Tecla(juego, 100, 100, TExit, ENull, 0));
}

void Combinaciones::draw() const{
	//for (int i = objetos.size() - 1; i >= 0; i--)
		//objetos[i]->draw();
	objetos[0]->draw();
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
