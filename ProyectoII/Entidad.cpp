#include "Entidad.h"


Entidad::Entidad(Juego*pJ, double x, double y, double w, double h, JuegoSDL::Texturas_t tex, JuegoSDL::Efectos_t efecto, Objetos_t tipo)
	: pJuego(pJ), rect({ x, y, w, h }), textura(tex), sonido(efecto), type (tipo)
{
	visible = true;
}

Entidad::~Entidad(){}

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
		pJuego->getResources()->getTextura(textura)->draw(pJuego->getRender(), rect,x,y,nullptr);//Dibujamos la textura

}

