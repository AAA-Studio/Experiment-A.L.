#ifndef Mundo_H
#define Mundo_H
#include "checkML.h"
#include "Estado.h"
#include <SDL.h>

//Clase abstracta que hereda de la raiz ObjetoJuego e implementa utilidades para las subclases
class Mundo : public Estado
{
protected:
	virtual void draw() const;
	virtual void onInput(SDL_Event &e);
	virtual void update();

public:
	Mundo(Juego * pJ);
	virtual ~Mundo();
	virtual bool colisionando(EntidadJuego* po1, EntidadJuego* po2);
	void newBala(EntidadJuego * po);
	void newBaja(EntidadJuego * po); // Los objetos informarán al juego cuando causen baja

private:
	bool pausa;
	void initObjetos();

};

#endif
