#ifndef _H_Combinaciones_H_
#define _H_Combinaciones_H_
#include "EstadoJuego.h"
#include "EntidadJuego.h"
#include "Juego.h"

class Combinaciones : public EstadoJuego
{
public:
	Combinaciones(Juego* juego);

	virtual void draw() const;
	virtual void update();
	virtual void onInput(SDL_Event &e);

	~Combinaciones();

protected:
	void initObjetos();
	vector <EntidadJuego*> objetos;
	Juego* juego;
};
#endif

