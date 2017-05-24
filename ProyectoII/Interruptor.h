#pragma once
#include "Entidad.h"
#include "Juego.h"


class Interruptor : public Entidad
{
public:
	Interruptor(Juego*pJ, double x, double y, double w, double h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto, Objetos_t tipo);
	~Interruptor();

	bool pulsado;
	void pulsar();

};

