#ifndef EntidadJuego_H
#define EntidadJuego_H
#include "checkML.h"
#include <SDL.h>


enum Objetos_t{ OInforme1, OInforme2, OLlave, ONull };

class EntidadJuego
{
	//M�todos publicos abstractos

public:

	EntidadJuego(){}

	virtual ~EntidadJuego(){}

	virtual void draw() const = 0;

	virtual void update() = 0;

	virtual void onInput() = 0;

	virtual SDL_Rect getRect() const = 0;

	virtual Objetos_t getType() const = 0;
};

#endif