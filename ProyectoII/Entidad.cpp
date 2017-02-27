#include "Entidad.h"


Entidad::Entidad(Juego*pJ, double x, double y, Texturas_t textura, Efectos_t efecto)
{
	ancho = alto = 100;
	posX = x;
	posY = y;
	pJuego = pJ;
	pTextura = textura;
	sonido = efecto;
	rect = { posX, posY, ancho, alto };

}

Entidad::~Entidad()
{
}

void Entidad::draw()const
{
	pJuego->getTextura(pTextura)->draw(pJuego->getRender(), rect);//Dibujamos la textura
}

SDL_Rect Entidad::dameRect(){
	SDL_Rect rectangulo;
	rectangulo.x = posX;
	rectangulo.y = posY;
	rectangulo.w = rect.w;
	rectangulo.h = rect.h;
	return rectangulo;
}