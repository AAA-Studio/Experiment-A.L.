#ifndef EntidadJuego_H
#define EntidadJuego_H
#include "checkML.h"
#include <stack>
#include "SDL.h"

enum Controles_t { SuperNULL, W, S, A, D,WA,WD,SA,SD, JPIUM, C, V };


class EntidadJuego
{
	//Métodos publicos abstractos

public:

	EntidadJuego(){}

	virtual ~EntidadJuego(){}

	virtual void draw() const = 0;

	virtual void update() = 0;

	virtual void onInput() = 0;

	virtual void coger() = 0;

	virtual void soltar(double x, double y) = 0;

	virtual const SDL_Rect getRect() = 0;
};

#endif