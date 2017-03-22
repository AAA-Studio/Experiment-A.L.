#ifndef _H_Leer_H_
#define _H_Leer_H_
#include "Estado.h"
class Leer : public Estado
{
public:
	Leer(Juego * pJ, Texturas_t textura);
	virtual void draw() const;
	virtual void update();
	~Leer();
protected:
	Texturas_t text;
	SDL_Rect rect;
};
#endif

