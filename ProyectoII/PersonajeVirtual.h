#ifndef PersonajeVirtual_H
#define PersonajeVirtual_H
#include "checkML.h"
#include "EntidadJuego.h"
#include "SDL.h"


//Clase abstracta que hereda de Entidad e implementa utilidades para Personaje
class PersonajeVirtual : virtual public EntidadJuego
{
public:
	virtual void destruyeBala(EntidadJuego * bala)=0;

	virtual void restaVida()=0;
	virtual int getVida()const = 0;
};

#endif