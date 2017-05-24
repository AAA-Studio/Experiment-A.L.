#include "Interruptor.h"


Interruptor::Interruptor(Juego*pJ, double x, double y, double w, double h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto, Objetos_t tipo) : Entidad(pJ, x, y, w, h, textura, efecto, tipo)
{
	tipo = OInterruptor;
}


Interruptor::~Interruptor()
{
}

void Interruptor::pulsar()
{
	if (pulsado) 
		pulsado = false;
	else
		pulsado = true;
}
