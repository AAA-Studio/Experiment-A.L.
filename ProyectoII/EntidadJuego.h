#ifndef EntidadJuego_H
#define EntidadJuego_H
#include "checkML.h"
#include <SDL.h>


enum Objetos_t{ OInforme1, OInforme2, OInforme3, OInforme4, OInforme5, OInforme6, OInforme7, OLlave, OTeclado, OPistola, OPildoras, OInterruptor1, OInterruptor2, ONull };

class EntidadJuego
{
	//M�todos publicos abstractos

public:

	EntidadJuego(){}

	virtual ~EntidadJuego(){}

	virtual void draw(int x, int y) const = 0;

	virtual void update() = 0;

	virtual void onInput() = 0;

	virtual SDL_Rect getRect() const = 0;

	virtual void setRect(SDL_Rect r) = 0;

	virtual Objetos_t getType() const = 0;

	virtual void setVisible(bool visible) = 0;

	virtual void move(int x, int y) = 0;
};

#endif