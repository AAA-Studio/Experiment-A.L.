#include "Armas.h"


Armas::Armas(Juego*pJ, double x, double y, double w, double h, int balas, int cadencia, Texturas_t textura, Efectos_t efecto, Objetos_t tipo) : Entidad(pJ, x, y, w, h, textura, efecto, ONull)
{
	this->balas = balas;
	this->cadencia = cadencia;
	time = SDL_GetTicks();
}


Armas::~Armas()
{
}

inline int Armas::getBalas(){
	return balas;
}
inline Uint32 Armas::getCadencia(){
	return cadencia;
}

inline void Armas::restaBalas(){
	balas--;
}