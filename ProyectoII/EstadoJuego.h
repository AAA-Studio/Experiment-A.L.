#ifndef EstadoJuego_H
#define EstadoJuego_H
#include "checkML.h"
#include <SDL.h>

class EstadoJuego
{
	//Padre supremo

public:

	EstadoJuego(){}

	virtual ~EstadoJuego(){}

	virtual void draw() const = 0;

	virtual void update() = 0;

	virtual bool onInput() = 0;

};

#endif

