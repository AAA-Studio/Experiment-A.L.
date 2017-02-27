#ifndef EntidadJuego_H
#define EntidadJuego_H
#include "checkML.h"
#include <stack>
#include <SDL.h>
enum Controles_t { SuperNULL, W, S, A, D,WA,WD,SA,SD, JPIUM };


class EntidadJuego
{
	//Métodos publicos abstractos

public:

	EntidadJuego(){}

	virtual ~EntidadJuego(){}

	virtual void draw() const = 0;

	virtual void update() = 0;

	virtual void onInput(const Controles_t &c) = 0;

	virtual SDL_Rect dameRect() = 0;
};

#endif