#ifndef EntidadJuego_H
#define EntidadJuego_H
#include "checkML.h"
#include <SDL.h>


enum Objetos_t{ OInforme1, OInforme2, OLlave, OTeclado,OAk47,OPildora, ONull };

class EntidadJuego
{
	//Métodos publicos abstractos

public:

	EntidadJuego(){}

	virtual ~EntidadJuego(){}

	virtual void draw(int x, int y) const = 0;

	virtual void update() = 0;

	virtual void onInput() = 0;

	virtual SDL_Rect getRect() const = 0;

	virtual Objetos_t getType() const = 0;

	virtual void setVisible(bool visible) = 0;

	virtual void move(int x, int y) = 0;

	virtual int getX() = 0;

	virtual int getY() = 0;

};

#endif