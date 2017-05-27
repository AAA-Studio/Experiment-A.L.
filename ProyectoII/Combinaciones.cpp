#include "Combinaciones.h"
#include "Boton.h"
#include "Entidad.h"
#include <iostream>
using namespace std;


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
	objetos.emplace_back(new Entidad(pJuego, 365, 480, 70, 80, JuegoSDL::TCero, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 275, 185, 70, 80, JuegoSDL::TUno, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 365, 185, 70, 80, JuegoSDL::TDos, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 455, 185, 70, 80, JuegoSDL::TTres, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 275, 285, 70, 80, JuegoSDL::TCuatro, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 365, 285, 70, 80, JuegoSDL::TCinco, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 455, 285, 70, 80, JuegoSDL::TSeis, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 275, 385, 70, 80, JuegoSDL::TSiete, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 365, 385, 70, 80, JuegoSDL::TOcho, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 455, 385, 70, 80, JuegoSDL::TNueve, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 275, 480, 70, 80, JuegoSDL::TVolver, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 455, 480, 70, 80, JuegoSDL::TEnter, JuegoSDL::ENull, ONull));
	objetos.emplace_back(new Entidad(pJuego, 200, 100, 400, 500, JuegoSDL::TKeypad, JuegoSDL::ENull, ONull));
	}

void Combinaciones::draw() const{
	//for (int i = objetos.size() - 1; i >= 0; i--)
		//objetos[i]->draw(objetos[i]->getRect().x, objetos[i]->getRect().y);
	//int i = 7;
	
	objetos[objetos.size() - 1]->draw(objetos[objetos.size() - 1]->getRect().x, objetos[objetos.size() - 1]->getRect().y);
	
	//objetos[boton]->draw(objetos[boton]->getRect().x, objetos[boton]->getRect().y);
	objetos[boton]->draw(objetos[boton]->getRect().x, objetos[boton]->getRect().y);
	
}

void Combinaciones::onInput(SDL_Event &e){

	if (e.type == SDL_KEYUP){ 
		if (e.key.keysym.sym == SDLK_RETURN) //si se pulsa la tecla enter
		{
			if (boton == 11)
				pulsaEnter(); //la tecla enter de teclado comprueba la combinacion
			else if (boton == 10) 
				pulsaSalir(); //la tecla salir nos devuelve a mundo
			else
			{
				combTecleada += to_string(boton);
				cout << " intentos: " + intentos;
				cout << " combinacion: " + combTecleada;
				intentos++;
			}
		}
		else if (e.key.keysym.sym == SDLK_RIGHT && boton != 3 && boton != 6 && boton != 9 && boton != 11) //ir al boton de la derecha
		{
			if (boton == 0)
				boton = 11; //si estamos en 0 vamos en enter
			else if (boton == 10)
				boton = 0; //si estamos en salir vamos a 0
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
}

void Combinaciones::pulsaEnter()
{
	if (acierto) //si acierta sale de combinaciones y la puerta se abre
	{
		pJuego->setPuerta(puerta, acierto);
		pJuego->popState();
	}
}

void Combinaciones::pulsaSalir() //metodo para salir de combinaciones en caso de que se pulse su tecla correspondiente
{
	pJuego->popState();
}