#ifndef PersonajeVirtual_H
#define PersonajeVirtual_H
#include "checkML.h"
#include "EntidadJuego.h"
#include "SDL.h"


//Clase abstracta que hereda de Entidad e implementa utilidades para Personaje
class PersonajeVirtual : virtual public EntidadJuego
{
public:

	virtual void restaVida() = 0;

	virtual float getVida()const = 0;

	virtual void mover(int x, int y) = 0;

};

#endif