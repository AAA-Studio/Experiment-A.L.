#ifndef Boton_H
#define Boton_H
#include "checkML.h"
#include "Entidad.h"


class Bala : public Entidad
{
public:
	Bala(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto);
	~Bala();
	virtual void update(){};

private:
};

#endif