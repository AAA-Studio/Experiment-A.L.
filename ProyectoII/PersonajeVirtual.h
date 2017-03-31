#ifndef PersonajeVirtual_H
#define PersonajeVirtual_H
#include "checkML.h"
#include "EntidadJuego.h"
#include "SDL.h"


//Clase abstracta que hereda de Entidad e implementa utilidades para Personaje
class PersonajeVirtual : public EntidadJuego
{
	
public:

	virtual void setCamera(SDL_Rect& camera)=0;

	virtual void destruyeBala(EntidadJuego * bala)=0;

	virtual void restaVida()=0;

};

#endif