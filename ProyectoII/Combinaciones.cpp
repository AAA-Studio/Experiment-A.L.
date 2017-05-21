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
}

void Combinaciones::update(){
	
	for (int i = 0; i < objetos.size(); i++)
		objetos[i]->update();

	if (combinacion == combTecleada)
	{
		acierto = true;
	}

	if (intentos == 4)
	{
		combTecleada = "";
		intentos = 0;
	}

	if (acierto)
	{
		pJuego->setPuerta(puerta, acierto);
		pJuego->popState();		
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
	objetos.emplace_back(new Boton(pJuego, 200, 100, 400, 500, JuegoSDL::TKeypad, JuegoSDL::ENull, enter));
	}

void Combinaciones::draw() const{
	//for (int i = objetos.size() - 1; i >= 0; i--)
		//objetos[i]->draw(objetos[i]->getRect().x, objetos[i]->getRect().y);
	//int i = 7;
	
	objetos[objetos.size() - 1]->draw(objetos[objetos.size() - 1]->getRect().x, objetos[objetos.size() - 1]->getRect().y);
	//objetos[i]->draw(objetos[i]->getRect().x, objetos[i]->getRect().y);
}

void Combinaciones::onInput(SDL_Event &e){

	if (e.type == SDL_MOUSEBUTTONUP)
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
	}

}

Combinaciones::~Combinaciones()
{
}
