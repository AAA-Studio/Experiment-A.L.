#ifndef MundoVirtual_H
#define MundoVirtual_H
#include "checkML.h"
#include "EstadoJuego.h"




//Clase abstracta que hereda de la raiz EstadoJuego
class MundoVirtual : public EstadoJuego
{

public:
	virtual void onInput(SDL_Event &e) = 0;
	virtual bool checkCollision(SDL_Rect a, SDL_Rect b) = 0;

};

#endif