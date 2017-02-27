#include "Personaje.h"
#include <iostream>

//Constructora
Personaje::Personaje(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto) : Entidad(pJ, x, y, textura, efecto)
{
}

//Destructora
Personaje::~Personaje()
{
}


//Actualiza el estado y devuelve false si el globo queda desinflado
void Personaje::update()
{

	
}

void Personaje::onInput(const Controles_t &c)
{
	double x = 0, y = 0;

	
		switch (c)
		{
		case SuperNULL:
			break;


		case WA:
			y += -0.1;
			x += -0.1;
			angulo = 135;
			break;

		case WD:
			y += -0.1;
			x += 0.1;
			angulo = 45;

			break;

		case SA:
			y += 0.1;
			x += -0.1;
			angulo = 225;
			break;

		case SD:
			y += 0.1;
			x += 0.1;
			angulo = 315;

			break;

		case W:
			y += -0.1;
			angulo = 90;
			break;

		case S:
			y += 0.1;
			angulo = 270;
			break;

		case A:
			x += -0.1;
			angulo = 180;
			break;

		case D:
			x += 0.1;
			angulo = 0;
			break;
		case JPIUM:
			disparo();
			break;
		}
		
	move(x, y);

}

void Personaje::move(double x, double y)
{
	posX += x;
	posY += y;

	rect = { posX, posY, ancho, alto };

}

void Personaje::disparo(){
	static_cast <Mundo*> (pJuego->topEstado())->newBala(this);
}





