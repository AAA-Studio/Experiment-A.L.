#ifndef Bala_H
#define Bala_H
#include "checkML.h"
#include "PersonajeVirtual.h"
#include "Entidad.h"
#include "MundoVirtual.h"


class Bala : public Entidad
{
public:
	Bala(MundoVirtual * pM, int x, int y, Texturas_t textura, Efectos_t efecto, int ang, ListaBalas_t tBala);
	~Bala();
	virtual void update();

private:
	int incrX,incrY;
	int velocidad;
	int angulo;
	const Uint32 duracion = 2000;
	Uint32 time;
	ListaBalas_t tipoBala;
	MundoVirtual * pMundo;

	void setAngulo();
};

#endif