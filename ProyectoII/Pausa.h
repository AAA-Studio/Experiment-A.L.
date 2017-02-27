#ifndef Pausa_H
#define Pausa_H
#include "Estado.h"

class Pausa : public Estado
{
public:
	Pausa(Juego * pJ);
	~Pausa();

	virtual void draw() const;
	virtual void onInput(SDL_Event &e);

private:
	void initObjetos();

};

#endif
