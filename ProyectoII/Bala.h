#ifndef Bala_H
#define Bala_H
#include "checkML.h"
#include "PersonajeVirtual.h"
#include "Entidad.h"
#include "MundoVirtual.h"


class Bala : public Entidad
{
public:
	Bala(MundoVirtual * pM, int x, int y,int ancho, int alto, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto, float ang, ListaBalas_t tBala);
	~Bala();

	virtual void update();
private:
	MundoVirtual * pMundo;
	ListaBalas_t tipoBala;
	float angulo;

	int velocidad;
	float incrX, incrY;

	const Uint32 duracion = 2000;
	Uint32 time;//Contador para autodestruccion

	void setAngulo();
};

#endif