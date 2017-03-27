#ifndef Bala_H
#define Bala_H
#include "checkML.h"
#include "PersonajeVirtual.h"
#include "Entidad.h"


class Bala : public Entidad
{
public:
	Bala(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto, int ang, PersonajeVirtual* per);
	~Bala();
	virtual void update();

private:
	int incrX,incrY;
	int velocidad;
	int angulo;
	const Uint32 duracion = 2000;
	Uint32 time;
	PersonajeVirtual* personaje;

	void setAngulo();

};

#endif