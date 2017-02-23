#include "Personaje.h"


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

		case JArriba:
			y += -0.01;
			break;

		case JAbajo:
			y += 0.01;
			break;

		case JIzquierda:
			x += -0.01;
			break;

		case JDerecha:
			x += 0.01;
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

void Personaje::disparo(int angulo){


}





