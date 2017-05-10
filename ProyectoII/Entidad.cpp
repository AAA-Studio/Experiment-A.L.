#include "Entidad.h"


Entidad::Entidad(Juego*pJ, double x, double y, double w, double h, Texturas_t textura, Efectos_t efecto, Objetos_t tipo)
{
	rect = { x, y, w,h };
	pJuego = pJ;
	pTextura = textura;
	sonido = efecto; 
	type = tipo;

}

Entidad::~Entidad()
{
}

void Entidad::draw(int x, int y)const
{
	pJuego->getTextura(pTextura)->draw(pJuego->getRender(), rect,x,y);//Dibujamos la textura
}

