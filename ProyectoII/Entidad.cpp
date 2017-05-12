#include "Entidad.h"


Entidad::Entidad(Juego*pJ, double x, double y, double w, double h, Texturas_t textura, Efectos_t efecto, Objetos_t tipo)
{
	rect = { x, y, w,h };
	pJuego = pJ;
	pTextura = textura;
	sonido = efecto; 
	type = tipo;
	visible = true;
}

Entidad::~Entidad()
{
}

void Entidad::move(int x, int y){
	rect.x += x;
	rect.y += y;

}

void  Entidad::setVisible(bool visible){ 
	this->visible = visible; 
}

void Entidad::draw(int x, int y)const
{
	if (visible)
		pJuego->getTextura(pTextura)->draw(pJuego->getRender(), rect,x,y,nullptr);//Dibujamos la textura
}

