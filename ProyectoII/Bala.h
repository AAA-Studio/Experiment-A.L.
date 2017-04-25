#ifndef Bala_H
#define Bala_H
#include "checkML.h"
#include "PersonajeVirtual.h"
#include "Entidad.h"
#include "MundoVirtual.h"


class Bala : public Entidad
{
public:
	Bala(MundoVirtual * pM, int x, int y, Texturas_t textura, Efectos_t efecto, float ang, ListaBalas_t tBala, int ancho, int alto);
	~Bala();
	virtual void update();

private:
	float incrX, incrY;
	int velocidad;
	float angulo;
	const Uint32 duracion = 2000;
	Uint32 time;
	ListaBalas_t tipoBala;
	MundoVirtual * pMundo;

	void setAngulo(int ancho, int alto);
};

#endif