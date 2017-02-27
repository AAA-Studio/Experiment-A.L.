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
	virtual void onClick();
	virtual void update();
	virtual bool colisionando(EntidadJuego * po1, EntidadJuego * po2);

public:
	Mundo(Juego * pJ);
	virtual ~Mundo();

	void newBaja(EntidadJuego * po); // Los objetos informarán al juego cuando causen baja

private:

	void initObjetos();

};

#endif
