#pragma once
#include "Entidad.h"
#include "Juego.h"
class Armas: public Entidad
{
public:
	Armas(Juego*pJ, double x, double y, double w, double h,int balas, int cadencia, Texturas_t textura, Efectos_t efecto, Objetos_t tipo);
	~Armas();
	void disparo();
	inline int getBalas(){ return balas; }
	inline Uint32 getCadencia(){ return cadencia; }
	inline void restaBalas(){ balas--; }
private:
	int balas=0;
	Uint32 cadencia=0;
	Uint32 time;
};

