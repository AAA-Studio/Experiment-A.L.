#pragma once
#include "Entidad.h"
#include "Juego.h"
class Pildoras : public Entidad
{
public:
	Pildoras(Juego*pJ, int x, int y, int w, int h, float salud, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto, Objetos_t tipo);
	~Pildoras();
	inline float getSalud(){ return salud; }
private:
	float salud;
};