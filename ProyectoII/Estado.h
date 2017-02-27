#ifndef Estado_H
#define Estado_H
#include "checkML.h"
#include "EstadoJuego.h"

#include <vector>

#include "Juego.h"
#include "EntidadJuego.h"

//Clase abstracta que hereda de la raiz EstadoJuego e implementa utilidades para las subclases
class Estado : public EstadoJuego
{
protected:
	virtual void draw() const;
	virtual void onInput(SDL_Event &e){};
	virtual void update();

	void freeObjetos();

	Juego * pJuego;
	vector <EntidadJuego*> objetos;

public:
	Estado(Juego * pJ);
	virtual ~Estado();
};

#endif

