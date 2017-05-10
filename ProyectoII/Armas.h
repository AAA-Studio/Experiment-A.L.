#pragma once
#include "Entidad.h"
#include "Juego.h"
class Armas: public Entidad
{
public:
	Armas(Juego*pJ, double x, double y, double w, double h,int balas, int cadencia, Texturas_t textura, Efectos_t efecto, Objetos_t tipo);
	~Armas();
	void disparo();
	int getBalas();
	inline Uint32 getCadencia();
	inline void restaBalas();
private:
	int balas=0;
	Uint32 cadencia=0;
	Uint32 time;
};

